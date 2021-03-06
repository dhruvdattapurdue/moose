#* This file is part of the MOOSE framework
#* https://www.mooseframework.org
#*
#* All rights reserved, see COPYRIGHT for full restrictions
#* https://github.com/idaholab/moose/blob/master/COPYRIGHT
#*
#* Licensed under LGPL 2.1, please see LICENSE for details
#* https://www.gnu.org/licenses/lgpl-2.1.html

class MooseException(Exception):
    """
    An Exception for MOOSE python applications.
    """

    def __init__(self, *args):
        message = ' '.join([str(x) for x in args])
        Exception.__init__(self, message)
