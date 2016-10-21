# python scripy to generate perfect hashing symbol table
#

import sys
import subprocess


# see gperf -m option
NUM_GPERF_ITERATIONS = 100


# attributes
Orderless = 0
Flat = 1
OneIdentity = 2
Listable = 3
Constant = 4
NumericFunction = 5
Protected = 6
Locked = 7
ReadProtected = 8
HoldFirst = 9
HoldRest = 10
HoldAll = 11
HoldAllComplete = 12
NHoldFirst = 13
NHoldRest = 14
NHoldAll = 15
SequenceHold = 16
Temporary = 17
Stub = 18


# builtins - Protected is assumed for all builtins
builtins = [
    ('List', Locked),
    ('Blank',),
    ('BlankSequence',),
    ('BlankNullSequence',),
    ('Pattern', HoldFirst),
    ('Alternatives',),
    ('Repeated',),
    ('RepeatedNull',),
    ('Except',),
    ('Longest',),
    ('Shortest',),
    ('OptionsPattern',),
    ('PatternSequence',),
    ('OrderlessPatternSequence', Orderless),
    ('Verbatim',),
    ('HoldPattern', HoldAll),
    ('KeyValuePattern',),
    ('Condition', HoldAll),
    ('PatternTest', HoldRest),
    ('Optional',),
    ('Plus', Flat, Listable, NumericFunction, OneIdentity, Orderless),
]


def _c_format_sequence(*items):
    return '{' + ', '.join(items) + '}'


def emit_c(f=sys.stdout):
    f.write('Symbol table[] = {\n')
    for name, *attrs in builtins:
        # prefix
        base = _c_format_sequence('0', 'SymbolType')
        c_name = '"%s"' % name
        nulls = ['NULL'] * 12

        # attributes
        attributes = ['0'] * 19
        for attr in attrs:
            attributes[attr] = '1'
        attributes[Protected] = '1'     # always protected
        attributes = _c_format_sequence(*attributes)

        # line
        line = _c_format_sequence(base, c_name, *nulls, attributes)
        f.write(' ' * 4 + line + ',\n')
    f.write('};\n')


def emit_gperf(f=sys.stdout):
    f.write('%%\n')
    for name, *attrs in builtins:
        f.write(name + '\n')
    f.write('%%\n')


def run_gperf():
    with open('builtin.gperf', 'w') as f:
        emit_gperf(f)
    print(subprocess.check_output(['gperf', '--no-strlen', '--multiple-iterations=%s' % NUM_GPERF_ITERATIONS, 'builtin.gperf']).decode('ascii'))


if __name__ == '__main__':
    emit_c()
    # emit_gperf()
    # run_gperf()
