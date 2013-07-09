"""Just a template for subclassing"""
import uuid, shutil, os, logging, fnmatch
from os.path import join, dirname, isdir, split
from jinja2 import Template
from contextlib import closing
from zipfile import ZipFile, ZIP_DEFLATED

from workspace_tools.toolchains import TOOLCHAIN_CLASSES
from workspace_tools.targets import TARGET_MAP

class OldLibrariesException(Exception): pass

class Exporter():
    TEMPLATE_DIR = dirname(__file__)
    DOT_IN_RELATIVE_PATH = False
    
    def __init__(self, target, inputDir, program_name, build_url_resolver):
        self.inputDir = inputDir
        self.target = target
        self.program_name = program_name
        self.toolchain = TOOLCHAIN_CLASSES[self.TOOLCHAIN](TARGET_MAP[target])
        self.build_url_resolver = build_url_resolver
    
    def __scan_and_copy(self, src_path, trg_path):
        resources = self.toolchain.scan_resources(src_path)
        
        for r_type in ['headers', 's_sources', 'c_sources', 'cpp_sources', 'objects', 'libraries', 'linker_script']:
            r = getattr(resources, r_type)
            if r:
                self.toolchain.copy_files(r, trg_path, rel_path=src_path)
        return resources.lib_builds
    
    def scan_and_copy_resources(self, prj_path, trg_path):
        # Copy only the file for the required target and toolchain
        lib_builds = []
        for src in ['lib', 'src']:
            lib_builds.extend(self.__scan_and_copy(join(prj_path, src), trg_path))
        
        # The libraries builds
        for bld in lib_builds:
            build_url = open(bld).read().strip()
            lib_data = self.build_url_resolver(build_url)
            lib_path = lib_data['path'].rstrip('\\/')
            self.__scan_and_copy(lib_path, join(trg_path, lib_data['name']))
        
        # Final scan of the actual exported resources
        self.resources = self.toolchain.scan_resources(trg_path)
        self.resources.relative_to(trg_path, self.DOT_IN_RELATIVE_PATH)
        # Check the existence of a binary build of the mbed library for the desired target
        # This prevents exporting the mbed libraries from source
        # if not self.toolchain.mbed_libs:
        #    raise OldLibrariesException()
    
    def gen_file(self, template_file, data, target_file):
        template_path = join(Exporter.TEMPLATE_DIR, template_file)
        template_text = open(template_path).read()
        template = Template(template_text)
        target_text = template.render(data)
        
        target_path = join(self.inputDir, target_file)
        logging.debug("Generating: %s" % target_path)
        open(target_path, "w").write(target_text)


def zip_working_directory_and_clean_up(tempdirectory=None, destination=None, program_name=None, clean=True):
    uid = str(uuid.uuid4())
    zipfilename = '%s.zip'%uid
    
    logging.debug("Zipping up %s to %s" % (tempdirectory,  join(destination, zipfilename)))
    # make zip
    def zipdir(basedir, archivename):
        assert isdir(basedir)
        fakeroot = program_name + '/'
        with closing(ZipFile(archivename, "w", ZIP_DEFLATED)) as z:
            for root, _, files in os.walk(basedir):
                # NOTE: ignore empty directories
                for fn in files:
                    absfn = join(root, fn)
                    zfn = fakeroot + '/' +  absfn[len(basedir)+len(os.sep):]
                    z.write(absfn, zfn)
    
    zipdir(tempdirectory, join(destination, zipfilename))
    
    if clean:
        shutil.rmtree(tempdirectory)
    
    return join(destination, zipfilename)
