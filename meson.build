project('plyr', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])


raydep = dependency('raylib')
tag = dependency('taglib_c')

exe = executable('plyr', 'plyr.c', dependencies : [raydep, tag],
  install : true)

test('basic', exe)
