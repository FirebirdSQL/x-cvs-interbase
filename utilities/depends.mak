# The contents of this file are subject to the Interbase Public
# License Version 1.0 (the "License"); you may not use this file
# except in compliance with the License. You may obtain a copy
# of the License at http://www.Inprise.com/IPL.html
#
# Software distributed under the License is distributed on an
# "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, either express
# or implied. See the License for the specific language governing
# rights and limitations under the License.
#
# The Original Code was created by Inprise Corporation
# and its predecessors. Portions created by Inprise Corporation are
# Copyright (C) Inprise Corporation.
#
# All Rights Reserved.
# Contributor(s): ______________________________________.
# depends.mak - utilities
# Created by 'make depends.mak'
# Created on 1998-11-25
analyse.o: analyse.c
analyse.o: source/jrd/common.h
cache.o: cache.c
cache.o: source/interbase/include/iberror.h
cache.o: source/jrd/build_no.h
cache.o: source/jrd/common.h
cache.o: source/jrd/fil.h
cache.o: source/jrd/gds.h
cache.o: source/jrd/gds_proto.h
cache.o: source/jrd/license.h
cache.o: source/jrd/thd.h
cache.o: source/jrd/why_proto.h
cmd_util.o: cmd_util.c
cmd_util.o: source/interbase/include/iberror.h
cmd_util.o: source/jrd/common.h
cmd_util.o: source/jrd/gds.h
cmd_util.o: source/jrd/isc.h
cmd_util.o: source/jrd/isc_s_proto.h
cmd_util.o: source/jrd/msg_encode.h
cmd_util.o: source/jrd/pwd.h
cmd_util.o: source/jrd/svc.h
cmd_util.o: source/jrd/svc_proto.h
cmd_util.o: source/jrd/svc_undoc.h
cmd_util.o: source/jrd/thd.h
dba.o: dba.c
dba.o: dbaswi.h
dba.o: ppg_proto.h
dba.o: source/interbase/include/iberror.h
dba.o: source/jrd/build_no.h
dba.o: source/jrd/common.h
dba.o: source/jrd/enc_proto.h
dba.o: source/jrd/fil.h
dba.o: source/jrd/gds.h
dba.o: source/jrd/gds_proto.h
dba.o: source/jrd/gdsassert.h
dba.o: source/jrd/ibsetjmp.h
dba.o: source/jrd/isc_f_proto.h
dba.o: source/jrd/license.h
dba.o: source/jrd/msg_encode.h
dba.o: source/jrd/ods.h
dba.o: source/jrd/thd.h
dba.o: source/jrd/time.h
drop.o: drop.c
drop.o: drpv3_proto.h
drop.o: source/jrd/build_no.h
drop.o: source/jrd/common.h
drop.o: source/jrd/fil.h
drop.o: source/jrd/file_params.h
drop.o: source/jrd/gds_proto.h
drop.o: source/jrd/isc.h
drop.o: source/jrd/isc_proto.h
drop.o: source/jrd/license.h
drop.o: source/jrd/thd.h
drop.o: source/lock/lock.h
dropv3.o: dropv3.c
dropv3.o: drpv3_proto.h
dropv3.o: source/jrd/build_no.h
dropv3.o: source/jrd/common.h
dropv3.o: source/jrd/isc.h
dropv3.o: source/jrd/isc_proto.h
dropv3.o: source/jrd/isc_s_proto.h
dropv3.o: source/jrd/license.h
dropv3.o: source/jrd/thd.h
dropv3.o: source/lock/fparamv3.h
dropv3.o: source/lock/lockv3.h
gsec.o: gsec.c
gsec.o: gsec.h
gsec.o: gsecswi.h
gsec.o: secur_proto.h
gsec.o: source/interbase/include/iberror.h
gsec.o: source/jrd/blk.h
gsec.o: source/jrd/build_no.h
gsec.o: source/jrd/common.h
gsec.o: source/jrd/dsc.h
gsec.o: source/jrd/fil.h
gsec.o: source/jrd/gds.h
gsec.o: source/jrd/gds_proto.h
gsec.o: source/jrd/gdsassert.h
gsec.o: source/jrd/ibsetjmp.h
gsec.o: source/jrd/isc.h
gsec.o: source/jrd/isc_s_proto.h
gsec.o: source/jrd/jrd.h
gsec.o: source/jrd/license.h
gsec.o: source/jrd/msg_encode.h
gsec.o: source/jrd/pwd.h
gsec.o: source/jrd/pwd_proto.h
gsec.o: source/jrd/svc.h
gsec.o: source/jrd/svc_proto.h
gsec.o: source/jrd/svc_undoc.h
gsec.o: source/jrd/thd.h
gsec.o: source/jrd/thd_proto.h
guard.o: guard.c
guard.o: source/jrd/common.h
guard.o: source/jrd/fil.h
guard.o: source/jrd/file_params.h
guard.o: source/jrd/gds_proto.h
guard.o: source/jrd/isc.h
guard.o: source/jrd/isc_proto.h
guard.o: source/jrd/thd.h
guard.o: util_proto.h
ibmgr.o: ibmgr.c
ibmgr.o: ibmgr.h
ibmgr.o: ibmgrswi.h
ibmgr.o: source/interbase/include/iberror.h
ibmgr.o: source/jrd/build_no.h
ibmgr.o: source/jrd/common.h
ibmgr.o: source/jrd/gds.h
ibmgr.o: source/jrd/license.h
ibmgr.o: srvrmgr_proto.h
install_reg.o: install_nt.h
install_reg.o: install_reg.c
install_reg.o: regis_proto.h
install_reg.o: source/jrd/build_no.h
install_reg.o: source/jrd/common.h
install_reg.o: source/jrd/license.h
install_svc.o: install_nt.h
install_svc.o: install_svc.c
install_svc.o: servi_proto.h
install_svc.o: source/jrd/build_no.h
install_svc.o: source/jrd/common.h
install_svc.o: source/jrd/license.h
ppg.o: ppg.c
ppg.o: source/interbase/include/iberror.h
ppg.o: source/jrd/common.h
ppg.o: source/jrd/fil.h
ppg.o: source/jrd/gds.h
ppg.o: source/jrd/gds_proto.h
ppg.o: source/jrd/ods.h
ppg.o: source/jrd/thd.h
ppg.o: source/jrd/time.h
print_pool.o: print_pool.c
print_pool.o: source/interbase/include/iberror.h
print_pool.o: source/jrd/common.h
print_pool.o: source/jrd/ibase.h
print_pool.o: source/jrd/svc_undoc.h
rebuild.o: rebui_proto.h
rebuild.o: rebuild.c
rebuild.o: rebuild.h
rebuild.o: rmet_proto.h
rebuild.o: rstor_proto.h
rebuild.o: source/interbase/include/iberror.h
rebuild.o: source/jrd/blk.h
rebuild.o: source/jrd/common.h
rebuild.o: source/jrd/dmp_proto.h
rebuild.o: source/jrd/dsc.h
rebuild.o: source/jrd/fil.h
rebuild.o: source/jrd/gds.h
rebuild.o: source/jrd/gds_proto.h
rebuild.o: source/jrd/gdsassert.h
rebuild.o: source/jrd/isc.h
rebuild.o: source/jrd/jrd.h
rebuild.o: source/jrd/ods.h
rebuild.o: source/jrd/pag.h
rebuild.o: source/jrd/thd.h
rebuild.o: source/jrd/time.h
rebuild.o: source/jrd/tra.h
registry.o: install_nt.h
registry.o: regis_proto.h
registry.o: registry.c
registry.o: source/jrd/build_no.h
registry.o: source/jrd/common.h
registry.o: source/jrd/license.h
relay.o: relay.c
relay.o: source/jrd/build_no.h
relay.o: source/jrd/common.h
relay.o: source/jrd/license.h
relay_mpexl.o: relay_mpexl.c
relay_mpexl.o: source/lock/lock_proto.h
relay_mpexl.o: source/jrd/aif_proto.h
relay_mpexl.o: source/jrd/build_no.h
relay_mpexl.o: source/jrd/common.h
relay_mpexl.o: source/jrd/event_proto.h
relay_mpexl.o: source/jrd/isc.h
relay_mpexl.o: source/jrd/isc_proto.h
relay_mpexl.o: source/jrd/isc_signal.h
relay_mpexl.o: source/jrd/license.h
relay_mpexl.o: source/jrd/mpexl.h
relay_mpexl.o: source/jrd/thd.h
run_service.o: run_service.c
run_service.o: source/interbase/include/iberror.h
run_service.o: source/jrd/common.h
run_service.o: source/jrd/fil.h
run_service.o: source/jrd/gds.h
run_service.o: source/jrd/gds_proto.h
run_service.o: source/jrd/thd.h
sbc_print.o: ppg_proto.h
sbc_print.o: sbc_print.c
sbc_print.o: source/jrd/common.h
sbc_print.o: source/jrd/fil.h
sbc_print.o: source/jrd/gds_proto.h
sbc_print.o: source/jrd/isc.h
sbc_print.o: source/jrd/isc_f_proto.h
sbc_print.o: source/jrd/isc_s_proto.h
sbc_print.o: source/jrd/llio.h
sbc_print.o: source/jrd/ods.h
sbc_print.o: source/jrd/thd.h
security.o: gsec.h
security.o: secur_proto.h
security.o: security.c
security.o: source/interbase/include/iberror.h
security.o: source/jrd/common.h
security.o: source/jrd/enc_proto.h
security.o: source/jrd/fil.h
security.o: source/jrd/gds.h
security.o: source/jrd/gds_proto.h
security.o: source/jrd/ibsetjmp.h
security.o: source/jrd/isc.h
security.o: source/jrd/isc_s_proto.h
security.o: source/jrd/pwd.h
security.o: source/jrd/svc.h
security.o: source/jrd/svc_proto.h
security.o: source/jrd/svc_undoc.h
security.o: source/jrd/thd.h
security.o: source/jrd/thd_proto.h
services.o: install_nt.h
services.o: servi_proto.h
services.o: services.c
services.o: source/jrd/build_no.h
services.o: source/jrd/common.h
services.o: source/jrd/license.h
srvrmgr.o: ibmgr.h
srvrmgr.o: source/interbase/include/iberror.h
srvrmgr.o: source/jrd/common.h
srvrmgr.o: source/jrd/gds.h
srvrmgr.o: source/jrd/gdsassert.h
srvrmgr.o: source/jrd/svc_undoc.h
srvrmgr.o: srvrmgr.c
srvrmgr.o: srvrmgr_proto.h
util.o: source/jrd/common.h
util.o: source/jrd/fil.h
util.o: source/jrd/gds_proto.h
util.o: source/jrd/gdsassert.h
util.o: source/jrd/thd.h
util.o: util.c
util.o: util_proto.h
v2_dmp.o: source/jrd/blk.h
v2_dmp.o: source/jrd/btr.h
v2_dmp.o: source/jrd/cch.h
v2_dmp.o: source/jrd/cch_proto.h
v2_dmp.o: source/jrd/common.h
v2_dmp.o: source/jrd/dmp_proto.h
v2_dmp.o: source/jrd/dsc.h
v2_dmp.o: source/jrd/gdsassert.h
v2_dmp.o: source/jrd/isc.h
v2_dmp.o: source/jrd/jrd.h
v2_dmp.o: source/jrd/ods.h
v2_dmp.o: source/jrd/pag.h
v2_dmp.o: source/jrd/pio.h
v2_dmp.o: source/jrd/thd.h
v2_dmp.o: source/jrd/time.h
v2_dmp.o: source/jrd/tra.h
v2_dmp.o: v2_dmp.c
