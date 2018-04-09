def Settings( **kwargs ):
  return {
    'flags': [
        '-x', 'c++',
        '-std=c++2a',
        '-Wall', '-Wextra', '-Werror',
        '-DAI_LOGGING_ENABLED',
        '-Iinclude/',
        '-Ideps/AI-Toolbox/include',
        '-Itest/',
        '-isystem/usr/include/eigen3/',
        '-isystem/usr/include/python3.8/'
    ],
  }
