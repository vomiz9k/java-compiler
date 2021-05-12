## build: in root dir:
### cmake ./ && make
#
## interpret:
### ./Compiler run input-filename
#
## if you have graphviz(dot) installed:
## test print ast:
### ./test_ast.sh
## and you can see cool derevya in .png format in tests/tree_making
#
## test print scope tree:
### ./test_scope.sh
#
## test compile errors with types:
### ./test_ce.sh
#
## test ir tree building:
### ./test_ir_tree.sh
#
## print IR tree splitted by functions:
### ./Compiler ir input-filename dir_for_output[must exist]
#
## run:
### ./Compiler [run/ast/scope/ir] input-filename [_dot-output-filename_ if ast]
