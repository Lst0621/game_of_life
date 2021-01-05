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


def update_file(target_fn, write_content):
    if os.path.exists(target_fn):
        with open(target_fn) as fd_read:
            read_content = fd_read.read()
        if (read_content == write_content):
            print('Identical content. No need for update!')
            return
    print('writing to {}'.format(target_fn))
    with open(target_fn, 'w') as fd_write:
        fd_write.write(write_content)


def main():
    dir = os.path.dirname(__file__)
    target_fn = os.path.join(dir, 'Playground.cpp')
    print("Generating {} ...".format(target_fn))

    max_dim = int(sys.argv[1])
    init_classes = ''.join(fill_template(dim) for dim in range(1, max_dim + 1))
    file_content = playground_cpp_template.format(init_classes)
    update_file(target_fn, file_content)


if __name__ == '__main__':
    main()
