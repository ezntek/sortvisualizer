project('sortvisualizer', 'c',
  version: '0.1.0',
  license: 'MIT')

dependencies = [
  dependency('raylib', version: '>=4.0.0')  
]

sources = [
  'src/main.c',
  'src/util.c',
  'src/algorithms/bubble.c',
  'src/algorithms/select.c',
  'src/algorithms/merge.c',
  'src/algorithms/insert.c',
  'src/array/array.c',
  'src/array/bar.c',
]

executable('sortvisualizer',
  sources,
  dependencies: dependencies
)
