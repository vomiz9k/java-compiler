### build: in root dir:
## cmake ./ && make
### interpret:
## ./Compiler run input-filename
### if you have graphviz(dot) installed:
### test print ast:
## ./test_ast.sh
### and you can see cool derevya in .png format in tests/tree_making
### test print scope tree:
## ./test_scope.sh
### test compile errors with types:
## ./test_ce.sh