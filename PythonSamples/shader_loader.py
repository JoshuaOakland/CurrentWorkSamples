import ctypes
from pyglet.gl import *
NULL = -1


def load_shader_source(target):
	infile = open(target, 'r')
	lines = infile.readlines()
	infile.close()
	source = ''
	for line in lines:
		source += line
	return(source)

def convert_shader_source(target):
	intermediate = ctypes.create_string_buffer(target.encode('utf-8'))
	target_source_in_c = ctypes.cast(ctypes.pointer(ctypes.pointer(intermediate)), ctypes.POINTER(ctypes.POINTER(GLchar)))
	return(target_source_in_c)

def get_length_of_source(file_path):
	'loads source, counts it, and returns count in ctype'
	return((GLsizei)(len(load_shader_source(instring))))

def check_shader_compilation(target,name):
	status = ctypes.c_int(0)

	glGetShaderiv(target, GL_COMPILE_STATUS, ctypes.byref(status))

	if(status):
		print("{0} has compiled successfully!".format(name))
	else:
		print("{0} has failed to compile...".format(name))

def check_program_link(target,name):
	status = ctypes.c_int(0)
	
	glGetProgramiv(target, GL_LINK_STATUS, ctypes.byref(status))

	if(status):
		print("{0} has linked successfully!".format(name))
	else:
		print("{0} has failed to link...".format(name))
