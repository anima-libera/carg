""" Python script _comp.py - Call gcc to compile the project """


#### OPTIONS

# Binary output options
bin_output_name = "CARG"
executable = True

# Compiling options
execute_after_compiling = False
warnings = True

# Directories options
bin_directory = "bin"
src_directory = "src"

# Link options
lib_links = ["SDL2_ttf"]
math = True
sdl2 = True
opengl = False


#### COMPILING SCRIPT

# Compute some file path things
bin_file = bin_output_name
bin_file_path = bin_directory+"/"+bin_file

# Compute the compiler options list compiler_options
compiler_options = []
if executable:
	compiler_options.append("-no-pie")
if warnings:
	compiler_options.append("-Wextra -Wall")

# Import os for system interaction and file linsting
import os

# List source file paths in src_file_paths
src_file_paths = []
for current_dir, dirs, files in os.walk(src_directory):
	for file in files:
		if file.split(".")[-1] == "c":
			src_file_paths.append(current_dir+"/"+file)

# Create compile command parts
str_src_input_files = " ".join(src_file_paths)
str_bin_output_file = "-o "+bin_file_path
str_compiler_options = " ".join(compiler_options)
if sdl2: str_sdl = "`sdl2-config --cflags --libs`"
else: str_sdl = ""
if math: str_math = "-lm"
else: str_math = ""
if opengl: str_opengl = "-lGL -lGLEW"
else: str_opengl = ""
str_links = " ".join(["-l"+lib for lib in lib_links])

# Compute the compile command and execute it
command = " ".join((
	"gcc",
	str_src_input_files,
	str_bin_output_file,
	str_compiler_options,
	str_opengl,
	str_sdl,
	str_math,
	str_links,
))
print(command)
os.system(command)


#### EXECUTE SCRIPT

# Execute the binary output if asked
if execute_after_compiling:
	os.system("./"+bin_file_path)
