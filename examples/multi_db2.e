/*
 * The contents of this file are subject to the Interbase Public
 * License Version 1.0 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy
 * of the License at http://www.Inprise.com/IPL.html
 *
 * Software distributed under the License is distributed on an
 * "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, either express
 * or implied. See the License for the specific language governing
 * rights and limitations under the License.
 *
 * The Original Code was created by Inprise Corporation
 * and its predecessors. Portions created by Inprise Corporation are
 * Copyright (C) Inprise Corporation.
 *
 * All Rights Reserved.
 * Contributor(s): ______________________________________.
 */
database db1 = filename "atlas.gdb";
database db2 = filename "c_guide.gdb";
database db3 = filename "nc_guide.gdb";
main ()
{
long		state_count;
state_count = 0;
exec sql select count (*) into :state_count from db1.states;
printf ("%d states in database 1\n", state_count);
exec sql select count (*) into :state_count from db2.states;
printf ("%d states in database 2\n", state_count);
exec sql select count (*) into :state_count from db3.states;
printf ("%d states in database 3\n", state_count);
exec sql commit release;
exit (0);
}
