from textwrap import dedent

from path import Path

import Boost.Cons
import zcons

import carefree


def program(cppfile):
    carefree_prefix, _ = carefree.resolve()
    name = str(Path(cppfile).splitext()[0])
    builddir = Path(cppfile).realpath().dirname()
    SConstruct = builddir / cppfile + '.scons'
    SConstruct.write_text(dedent("""
    from path import Path

    import cfo.scons


    env = cfo.scons.Environment({!r})

    env.Prepend(CPPPATH={!r})
    env.Append(LIBS=['msvcrtd'])

    env.Program({!r}, {!r})
    """.format(name, carefree_prefix / 'include', name, cppfile)))
    zcons.scons(['-f', SConstruct], DEBUG=True)
