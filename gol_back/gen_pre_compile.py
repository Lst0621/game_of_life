import os
import sys

template = \
    'template class PlayGround<{}>;\n' \
    'template class VectorGrid<{}>;\n'
playground_cpp_template = \
    '#include "Playground.h"\n' \
    '#include "VectorGrid.h"\n' \
    '\n' \
    'namespace lst {{\n' \
    'namespace gol {{\n' \
    '{}' \
    '}}  // namespace gol\n' \
    '}}  // namespace lst'


def fill_template(dim):
    return template.format(dim, dim)


def main():
    max_dim = int(sys.argv[1])
    init_classes = ''.join(fill_template(dim) for dim in range(1, max_dim + 1))
    dir = os.path.dirname(__file__)
    target_fn = os.path.join(dir, 'Playground.cpp')
    file_content = playground_cpp_template.format(init_classes)
    print('writing to {}'.format(target_fn))
    with open(target_fn, 'w') as fd:
        fd.write(file_content)


if __name__ == '__main__':
    main()
