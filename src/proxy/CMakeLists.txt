######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
INSTALL(PROGRAMS htopml-slurm-proxy.py
        DESTINATION bin RENAME htopml-slurm-proxy)
INSTALL(PROGRAMS htopml-workstation-slurm-proxy.py
        DESTINATION bin RENAME htopml-workstation-slurm-proxy)
