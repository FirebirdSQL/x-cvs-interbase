/*
 *	PROGRAM:	JRD Access Method
 *	MODULE:		trig.h
 *	DESCRIPTION:	System-defined triggers
 *
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
#ifndef _JRD_TRIG_H_
#define _JRD_TRIG_H_

/* This file contains the trigger blr for the system-defined triggers
   on system relations.  The GDEF source for these triggers is in
   GRANT.GDL in the JRD component.  When modifying a system trigger,
   check out GRANT.GDL, modify the trigger source to generate the
   proper blr, replace the blr in TRIG.H, and check both files back in. */

/* NOTE:
   The blr in trigger 1 has been manually changed to add a substring
   operation to the four concatenations of SQL$ and the relation name.
   This blr cannot be generate by gdef.  The modified blr is:

       blr_substring,
       blr_concatenate, 
          blr_literal, blr_text, 4,0, 'S','Q','L','$',
          blr_field, 5, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E', 
       blr_literal, blr_long, 0, 0,0,0,0,
       blr_literal, blr_long, 0, 31,0,0,0,
*/

/* trigger definition structure */

typedef struct trg {
    CONST SCHAR	*trg_name;
    UCHAR	trg_relation;
    UCHAR	trg_type;
    USHORT	trg_length;
    CONST UCHAR	*trg_blr;
    USHORT      trg_flags;
    UCHAR       trg_ods_version;
} TRG;

/* trigger message structure */

typedef struct trigger_msg {
    CONST SCHAR	*trigmsg_name;
    USHORT	trigmsg_number;
    CONST SCHAR	*trigmsg_text;
    UCHAR       trg_ods_version;
} TRIGMSG;

/* generator definition structure */

typedef struct gen {
    CONST SCHAR	*gen_name;
    USHORT	gen_id;
} GEN;

/* generators needed by the system triggers */

static CONST GEN generators [] = {
    "RDB$SECURITY_CLASS", 0,
    "SQL$DEFAULT", 0,
    "RDB$PROCEDURES", 0,
    "RDB$EXCEPTIONS", 0,
    "RDB$CONSTRAINT_NAME", 0,
    "RDB$FIELD_NAME", 0,
    "RDB$INDEX_NAME", 0,
    "RDB$TRIGGER_NAME", 0,
    0, 0
};

/* here is trigger 1, along with its messages */

/******
static CONST TEXT trigger_1_msg_0 [] = "could not find relation/procedure for GRANT";
static CONST TEXT trigger_1_msg_1 [] = "could not find field for GRANT";
static CONST TEXT trigger_1_msg_2 [] = "user does not have GRANT privileges for operation";
static CONST TEXT trigger_1_msg_3 [] = "relation/procedure has non-SQL security class defined";
static CONST TEXT trigger_1_msg_4 [] = "field has non-SQL security class defined";
static CONST TEXT trigger_1_msg_5 [] = "user does not have GRANT privileges on base table/view for operation";
******/

static CONST UCHAR FAR_VARIABLE trigger1 [] = 
{
/* NOTE:
   The blr in trigger 1 has been manually changed to add a substring
   operation to the four concatenations of SQL$ and the relation name.
   This avoids the generation of security class names that are longer
   than 32 characters.
   This blr cannot be generate by gdef.  The modified blr is:

       blr_substring,
       blr_concatenate, 
          blr_literal, blr_text, 4,0, 'S','Q','L','$',
          blr_field, 5, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E', 
       blr_literal, blr_long, 0, 0,0,0,0,
       blr_literal, blr_long, 0, 31,0,0,0,
*/
            blr_version5,
            blr_begin,
               blr_if,
                  blr_eql,
                     blr_field, 1, 15, 'R','D','B','$','O','B','J','E','C','T','_','T','Y','P','E',
                     blr_literal, blr_long, 0, 0,0,0,0,
                  blr_begin,
                     blr_if,
                        blr_not,
                           blr_any,
                              blr_rse, 1,
                                 blr_relation, 13, 'R','D','B','$','R','E','L','A','T','I','O','N','S', 3,
                                 blr_boolean,
                                    blr_eql,
                                       blr_field, 3, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                       blr_field, 1, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                 blr_end,
                        blr_leave, 0,
                        blr_end,
                     blr_if,
                        blr_not,
                           blr_missing,
                              blr_field, 1, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E',
                        blr_if,
                           blr_not,
                              blr_any,
                                 blr_rse, 1,
                                    blr_relation, 19, 'R','D','B','$','R','E','L','A','T','I','O','N','_','F','I','E','L','D','S', 4,
                                    blr_boolean,
                                       blr_and,
                                          blr_eql,
                                             blr_field, 4, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                             blr_field, 1, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                          blr_eql,
                                             blr_field, 4, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E',
                                             blr_field, 1, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E',
                                    blr_end,
                           blr_leave, 1,
                           blr_end,
                        blr_end,
                     blr_end,
                  blr_end,
               blr_if,
                  blr_and,
                     blr_eql,
                        blr_field, 1, 15, 'R','D','B','$','O','B','J','E','C','T','_','T','Y','P','E',
                        blr_literal, blr_long, 0, 5,0,0,0,
                     blr_not,
                        blr_any,
                           blr_rse, 1,
                              blr_relation, 14, 'R','D','B','$','P','R','O','C','E','D','U','R','E','S', 5,
                              blr_boolean,
                                 blr_eql,
                                    blr_field, 5, 18, 'R','D','B','$','P','R','O','C','E','D','U','R','E','_','N','A','M','E',
                                    blr_field, 1, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                              blr_end,
                  blr_leave, 0,
                  blr_end,
               blr_if,
                  blr_or,
                     blr_eql,
                        blr_field, 1, 13, 'R','D','B','$','U','S','E','R','_','T','Y','P','E',
                        blr_literal, blr_long, 0, 0,0,0,0,
                     blr_or,
                        blr_eql,
                           blr_field, 1, 13, 'R','D','B','$','U','S','E','R','_','T','Y','P','E',
                           blr_literal, blr_long, 0, 3,0,0,0,
                        blr_or,
                           blr_eql,
                              blr_field, 1, 13, 'R','D','B','$','U','S','E','R','_','T','Y','P','E',
                              blr_literal, blr_long, 0, 4,0,0,0,
                           blr_or,
                              blr_eql,
                                 blr_field, 1, 13, 'R','D','B','$','U','S','E','R','_','T','Y','P','E',
                                 blr_literal, blr_long, 0, 6,0,0,0,
                              blr_or,
                                 blr_eql,
                                    blr_field, 1, 13, 'R','D','B','$','U','S','E','R','_','T','Y','P','E',
                                    blr_literal, blr_long, 0, 7,0,0,0,
                                 blr_or,
                                    blr_eql,
                                       blr_field, 1, 13, 'R','D','B','$','U','S','E','R','_','T','Y','P','E',
                                       blr_literal, blr_long, 0, 8,0,0,0,
                                    blr_or,
                                       blr_eql,
                                          blr_field, 1, 13, 'R','D','B','$','U','S','E','R','_','T','Y','P','E',
                                          blr_literal, blr_long, 0, 9,0,0,0,
                                       blr_or,
                                          blr_eql,
                                             blr_field, 1, 13, 'R','D','B','$','U','S','E','R','_','T','Y','P','E',
                                             blr_literal, blr_long, 0, 10,0,0,0,
                                          blr_or,
                                             blr_eql,
                                                blr_field, 1, 13, 'R','D','B','$','U','S','E','R','_','T','Y','P','E',
                                                blr_literal, blr_long, 0, 11,0,0,0,
                                             blr_eql,
                                                blr_field, 1, 13, 'R','D','B','$','U','S','E','R','_','T','Y','P','E',
                                                blr_literal, blr_long, 0, 12,0,0,0,
                  blr_assignment,
                     blr_upcase,
                        blr_field, 1, 8, 'R','D','B','$','U','S','E','R',
                     blr_field, 1, 8, 'R','D','B','$','U','S','E','R',
                  blr_end,
               blr_if,
                  blr_missing,
                     blr_field, 1, 11, 'R','D','B','$','G','R','A','N','T','O','R',
                  blr_assignment,
                     blr_upcase,
                        blr_user_name,
                     blr_field, 1, 11, 'R','D','B','$','G','R','A','N','T','O','R',
                  blr_end,
               blr_if,
                  blr_eql,
                     blr_field, 1, 15, 'R','D','B','$','O','B','J','E','C','T','_','T','Y','P','E',
                     blr_literal, blr_long, 0, 0,0,0,0,
                  blr_begin,
                     blr_for,
                        blr_rse, 1,
                           blr_relation, 13, 'R','D','B','$','R','E','L','A','T','I','O','N','S', 6,
                           blr_boolean,
                              blr_eql,
                                 blr_field, 6, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                 blr_field, 1, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                           blr_end,
                        blr_begin,
                           blr_if,
                              blr_or,
                                 blr_and,
                                    blr_eql,
                                       blr_field, 6, 14, 'R','D','B','$','O','W','N','E','R','_','N','A','M','E',
                                       blr_upcase,
                                          blr_user_name,
                                    blr_and,
                                       blr_eql,
                                          blr_field, 6, 14, 'R','D','B','$','O','W','N','E','R','_','N','A','M','E',
                                          blr_field, 1, 11, 'R','D','B','$','G','R','A','N','T','O','R',
                                       blr_eql,
                                          blr_field, 6, 14, 'R','D','B','$','O','W','N','E','R','_','N','A','M','E',
                                          blr_field, 1, 8, 'R','D','B','$','U','S','E','R',
                                 blr_eql,
                                    blr_upcase,
                                       blr_user_name,
                                    blr_literal, blr_text, 6,0, 'S','Y','S','D','B','A',
                              blr_begin,
                                 blr_end,
                              blr_if,
                                 blr_neq,
                                    blr_field, 6, 14, 'R','D','B','$','O','W','N','E','R','_','N','A','M','E',
                                    blr_upcase,
                                       blr_user_name,
                                 blr_begin,
                                    blr_if,
                                       blr_not,
                                          blr_any,
                                             blr_rse, 1,
                                                blr_relation, 19, 'R','D','B','$','U','S','E','R','_','P','R','I','V','I','L','E','G','E','S', 7,
                                                blr_boolean,
                                                   blr_and,
                                                      blr_eql,
                                                         blr_field, 7, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                                         blr_field, 1, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                                      blr_and,
                                                         blr_eql,
                                                            blr_field, 7, 15, 'R','D','B','$','O','B','J','E','C','T','_','T','Y','P','E',
                                                            blr_literal, blr_long, 0, 0,0,0,0,
                                                         blr_and,
                                                            blr_eql,
                                                               blr_field, 7, 13, 'R','D','B','$','P','R','I','V','I','L','E','G','E',
                                                               blr_field, 1, 13, 'R','D','B','$','P','R','I','V','I','L','E','G','E',
                                                            blr_and,
                                                               blr_eql,
                                                                  blr_field, 7, 8, 'R','D','B','$','U','S','E','R',
                                                                  blr_field, 1, 11, 'R','D','B','$','G','R','A','N','T','O','R',
                                                               blr_and,
                                                                  blr_eql,
                                                                     blr_field, 7, 13, 'R','D','B','$','U','S','E','R','_','T','Y','P','E',
                                                                     blr_literal, blr_long, 0, 8,0,0,0,
                                                                  blr_and,
                                                                     blr_neq,
                                                                        blr_field, 7, 16, 'R','D','B','$','G','R','A','N','T','_','O','P','T','I','O','N',
                                                                        blr_literal, blr_long, 0, 0,0,0,0,
                                                                     blr_or,
                                                                        blr_missing,
                                                                           blr_field, 7, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E',
                                                                        blr_eql,
                                                                           blr_field, 7, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E',
                                                                           blr_field, 1, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E',
                                                blr_end,
                                       blr_leave, 2,
                                       blr_end,
                                    blr_end,
                                 blr_if,
                                    blr_not,
                                       blr_missing,
                                          blr_field, 1, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E',
                                    blr_begin,
                                       blr_for,
                                          blr_rse, 3,
                                             blr_relation, 19, 'R','D','B','$','R','E','L','A','T','I','O','N','_','F','I','E','L','D','S', 8,
                                             blr_relation, 18, 'R','D','B','$','V','I','E','W','_','R','E','L','A','T','I','O','N','S', 9,
                                             blr_relation, 13, 'R','D','B','$','R','E','L','A','T','I','O','N','S', 10,
                                             blr_boolean,
                                                blr_and,
                                                   blr_eql,
                                                      blr_field, 8, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E',
                                                      blr_field, 1, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E',
                                                   blr_and,
                                                      blr_eql,
                                                         blr_field, 8, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                                         blr_field, 1, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                                      blr_and,
                                                         blr_not,
                                                            blr_missing,
                                                               blr_field, 8, 14, 'R','D','B','$','B','A','S','E','_','F','I','E','L','D',
                                                         blr_and,
                                                            blr_eql,
                                                               blr_field, 9, 13, 'R','D','B','$','V','I','E','W','_','N','A','M','E',
                                                               blr_field, 8, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                                            blr_and,
                                                               blr_eql,
                                                                  blr_field, 9, 16, 'R','D','B','$','V','I','E','W','_','C','O','N','T','E','X','T',
                                                                  blr_field, 8, 16, 'R','D','B','$','V','I','E','W','_','C','O','N','T','E','X','T',
                                                               blr_eql,
                                                                  blr_field, 9, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                                                  blr_field, 10, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                             blr_end,
                                          blr_begin,
                                             blr_if,
                                                blr_and,
                                                   blr_neq,
                                                      blr_field, 10, 14, 'R','D','B','$','O','W','N','E','R','_','N','A','M','E',
                                                      blr_field, 6, 14, 'R','D','B','$','O','W','N','E','R','_','N','A','M','E',
                                                   blr_neq,
                                                      blr_upcase,
                                                         blr_user_name,
                                                      blr_literal, blr_text, 6,0, 'S','Y','S','D','B','A',
                                                blr_begin,
                                                   blr_if,
                                                      blr_not,
                                                         blr_any,
                                                            blr_rse, 1,
                                                               blr_relation, 19, 'R','D','B','$','U','S','E','R','_','P','R','I','V','I','L','E','G','E','S', 11,
                                                               blr_boolean,
                                                                  blr_and,
                                                                     blr_eql,
                                                                        blr_field, 11, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                                                        blr_field, 10, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                                                     blr_and,
                                                                        blr_eql,
                                                                           blr_field, 11, 15, 'R','D','B','$','O','B','J','E','C','T','_','T','Y','P','E',
                                                                           blr_literal, blr_long, 0, 0,0,0,0,
                                                                        blr_and,
                                                                           blr_eql,
                                                                              blr_field, 11, 13, 'R','D','B','$','P','R','I','V','I','L','E','G','E',
                                                                              blr_field, 1, 13, 'R','D','B','$','P','R','I','V','I','L','E','G','E',
                                                                           blr_and,
                                                                              blr_eql,
                                                                                 blr_field, 11, 8, 'R','D','B','$','U','S','E','R',
                                                                                 blr_field, 6, 14, 'R','D','B','$','O','W','N','E','R','_','N','A','M','E',
                                                                              blr_and,
                                                                                 blr_eql,
                                                                                    blr_field, 11, 13, 'R','D','B','$','U','S','E','R','_','T','Y','P','E',
                                                                                    blr_literal, blr_long, 0, 8,0,0,0,
                                                                                 blr_and,
                                                                                    blr_neq,
                                                                                       blr_field, 11, 16, 'R','D','B','$','G','R','A','N','T','_','O','P','T','I','O','N',
                                                                                       blr_literal, blr_long, 0, 0,0,0,0,
                                                                                    blr_or,
                                                                                       blr_missing,
                                                                                          blr_field, 11, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E',
                                                                                       blr_eql,
                                                                                          blr_field, 11, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E',
                                                                                          blr_field, 8, 14, 'R','D','B','$','B','A','S','E','_','F','I','E','L','D',
                                                               blr_end,
                                                      blr_leave, 5,
                                                      blr_end,
                                                   blr_end,
                                                blr_end,
                                             blr_end,
                                       blr_end,
                                    blr_begin,
                                       blr_for,
                                          blr_rse, 2,
                                             blr_relation, 18, 'R','D','B','$','V','I','E','W','_','R','E','L','A','T','I','O','N','S', 12,
                                             blr_relation, 13, 'R','D','B','$','R','E','L','A','T','I','O','N','S', 13,
                                             blr_boolean,
                                                blr_and,
                                                   blr_eql,
                                                      blr_field, 12, 13, 'R','D','B','$','V','I','E','W','_','N','A','M','E',
                                                      blr_field, 1, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                                   blr_eql,
                                                      blr_field, 12, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                                      blr_field, 13, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                             blr_end,
                                          blr_begin,
                                             blr_if,
                                                blr_and,
                                                   blr_neq,
                                                      blr_field, 13, 14, 'R','D','B','$','O','W','N','E','R','_','N','A','M','E',
                                                      blr_field, 6, 14, 'R','D','B','$','O','W','N','E','R','_','N','A','M','E',
                                                   blr_neq,
                                                      blr_upcase,
                                                         blr_user_name,
                                                      blr_literal, blr_text, 6,0, 'S','Y','S','D','B','A',
                                                blr_begin,
                                                   blr_if,
                                                      blr_not,
                                                         blr_any,
                                                            blr_rse, 1,
                                                               blr_relation, 19, 'R','D','B','$','U','S','E','R','_','P','R','I','V','I','L','E','G','E','S', 14,
                                                               blr_boolean,
                                                                  blr_and,
                                                                     blr_eql,
                                                                        blr_field, 14, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                                                        blr_field, 13, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                                                     blr_and,
                                                                        blr_eql,
                                                                           blr_field, 14, 15, 'R','D','B','$','O','B','J','E','C','T','_','T','Y','P','E',
                                                                           blr_literal, blr_long, 0, 0,0,0,0,
                                                                        blr_and,
                                                                           blr_eql,
                                                                              blr_field, 14, 13, 'R','D','B','$','P','R','I','V','I','L','E','G','E',
                                                                              blr_field, 1, 13, 'R','D','B','$','P','R','I','V','I','L','E','G','E',
                                                                           blr_and,
                                                                              blr_eql,
                                                                                 blr_field, 14, 8, 'R','D','B','$','U','S','E','R',
                                                                                 blr_field, 6, 14, 'R','D','B','$','O','W','N','E','R','_','N','A','M','E',
                                                                              blr_and,
                                                                                 blr_eql,
                                                                                    blr_field, 14, 13, 'R','D','B','$','U','S','E','R','_','T','Y','P','E',
                                                                                    blr_literal, blr_long, 0, 8,0,0,0,
                                                                                 blr_and,
                                                                                    blr_neq,
                                                                                       blr_field, 14, 16, 'R','D','B','$','G','R','A','N','T','_','O','P','T','I','O','N',
                                                                                       blr_literal, blr_long, 0, 0,0,0,0,
                                                                                    blr_missing,
                                                                                       blr_field, 14, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E',
                                                               blr_end,
                                                      blr_leave, 5,
                                                      blr_end,
                                                   blr_end,
                                                blr_end,
                                             blr_end,
                                       blr_end,
                           blr_if,
                              blr_missing,
                                 blr_field, 6, 18, 'R','D','B','$','S','E','C','U','R','I','T','Y','_','C','L','A','S','S',
                              blr_modify, 6, 15,
                                 blr_begin,
                                    blr_assignment,
blr_substring,
                                       blr_concatenate,
                                          blr_literal, blr_text, 4,0, 'S','Q','L','$',
                                          blr_field, 6, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
blr_literal, blr_long, 0, 0,0,0,0,
blr_literal, blr_long, 0, 31,0,0,0,
                                       blr_field, 15, 18, 'R','D','B','$','S','E','C','U','R','I','T','Y','_','C','L','A','S','S',
                                    blr_end,
                              blr_if,
                                 blr_neq,
                                    blr_field, 6, 18, 'R','D','B','$','S','E','C','U','R','I','T','Y','_','C','L','A','S','S',
blr_substring,
                                    blr_concatenate,
                                       blr_literal, blr_text, 4,0, 'S','Q','L','$',
                                       blr_field, 6, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
blr_literal, blr_long, 0, 0,0,0,0,
blr_literal, blr_long, 0, 31,0,0,0,
                                 blr_leave, 3,
                                 blr_end,
                           blr_end,
                     blr_if,
                        blr_not,
                           blr_missing,
                              blr_field, 1, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E',
                        blr_for,
                           blr_rse, 1,
                              blr_relation, 19, 'R','D','B','$','R','E','L','A','T','I','O','N','_','F','I','E','L','D','S', 16,
                              blr_boolean,
                                 blr_and,
                                    blr_eql,
                                       blr_field, 16, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                       blr_field, 1, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                    blr_eql,
                                       blr_field, 16, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E',
                                       blr_field, 1, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E',
                              blr_end,
                           blr_begin,
                              blr_if,
                                 blr_missing,
                                    blr_field, 16, 18, 'R','D','B','$','S','E','C','U','R','I','T','Y','_','C','L','A','S','S',
                                 blr_modify, 16, 17,
                                    blr_begin,
                                       blr_assignment,
                                          blr_concatenate,
                                             blr_literal, blr_text, 9,0, 'S','Q','L','$','G','R','A','N','T',
                                             blr_gen_id, 18, 'R','D','B','$','S','E','C','U','R','I','T','Y','_','C','L','A','S','S',
                                                blr_literal, blr_long, 0, 1,0,0,0,
                                          blr_field, 17, 18, 'R','D','B','$','S','E','C','U','R','I','T','Y','_','C','L','A','S','S',
                                       blr_end,
                                 blr_if,
                                    blr_not,
                                       blr_starting,
                                          blr_field, 16, 18, 'R','D','B','$','S','E','C','U','R','I','T','Y','_','C','L','A','S','S',
                                          blr_literal, blr_text, 9,0, 'S','Q','L','$','G','R','A','N','T',
                                    blr_leave, 4,
                                    blr_end,
                              blr_end,
                        blr_end,
                     blr_end,
                  blr_if,
                     blr_eql,
                        blr_field, 1, 15, 'R','D','B','$','O','B','J','E','C','T','_','T','Y','P','E',
                        blr_literal, blr_long, 0, 5,0,0,0,
                     blr_for,
                        blr_rse, 1,
                           blr_relation, 14, 'R','D','B','$','P','R','O','C','E','D','U','R','E','S', 18,
                           blr_boolean,
                              blr_eql,
                                 blr_field, 18, 18, 'R','D','B','$','P','R','O','C','E','D','U','R','E','_','N','A','M','E',
                                 blr_field, 1, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                           blr_end,
                        blr_begin,
                           blr_if,
                              blr_and,
                                 blr_neq,
                                    blr_field, 18, 14, 'R','D','B','$','O','W','N','E','R','_','N','A','M','E',
                                    blr_upcase,
                                       blr_user_name,
                                 blr_neq,
                                    blr_upcase,
                                       blr_user_name,
                                    blr_literal, blr_text, 6,0, 'S','Y','S','D','B','A',
                              blr_if,
                                 blr_not,
                                    blr_any,
                                       blr_rse, 1,
                                          blr_relation, 19, 'R','D','B','$','U','S','E','R','_','P','R','I','V','I','L','E','G','E','S', 19,
                                          blr_boolean,
                                             blr_and,
                                                blr_eql,
                                                   blr_field, 19, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                                   blr_field, 1, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                                blr_and,
                                                   blr_eql,
                                                      blr_field, 19, 15, 'R','D','B','$','O','B','J','E','C','T','_','T','Y','P','E',
                                                      blr_literal, blr_long, 0, 5,0,0,0,
                                                   blr_and,
                                                      blr_eql,
                                                         blr_field, 19, 13, 'R','D','B','$','P','R','I','V','I','L','E','G','E',
                                                         blr_field, 1, 13, 'R','D','B','$','P','R','I','V','I','L','E','G','E',
                                                      blr_and,
                                                         blr_eql,
                                                            blr_field, 19, 8, 'R','D','B','$','U','S','E','R',
                                                            blr_field, 1, 11, 'R','D','B','$','G','R','A','N','T','O','R',
                                                         blr_and,
                                                            blr_eql,
                                                               blr_field, 19, 13, 'R','D','B','$','U','S','E','R','_','T','Y','P','E',
                                                               blr_literal, blr_long, 0, 8,0,0,0,
                                                            blr_and,
                                                               blr_neq,
                                                                  blr_field, 19, 16, 'R','D','B','$','G','R','A','N','T','_','O','P','T','I','O','N',
                                                                  blr_literal, blr_long, 0, 0,0,0,0,
                                                               blr_or,
                                                                  blr_missing,
                                                                     blr_field, 19, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E',
                                                                  blr_eql,
                                                                     blr_field, 19, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E',
                                                                     blr_field, 1, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E',
                                          blr_end,
                                 blr_leave, 2,
                                 blr_end,
                              blr_end,
                           blr_if,
                              blr_missing,
                                 blr_field, 18, 18, 'R','D','B','$','S','E','C','U','R','I','T','Y','_','C','L','A','S','S',
                              blr_modify, 18, 20,
                                 blr_begin,
                                    blr_assignment,
blr_substring,
                                       blr_concatenate,
                                          blr_literal, blr_text, 4,0, 'S','Q','L','$',
                                          blr_field, 18, 18, 'R','D','B','$','P','R','O','C','E','D','U','R','E','_','N','A','M','E',
blr_literal, blr_long, 0, 0,0,0,0,
blr_literal, blr_long, 0, 31,0,0,0,
                                       blr_field, 20, 18, 'R','D','B','$','S','E','C','U','R','I','T','Y','_','C','L','A','S','S',
                                    blr_end,
                              blr_if,
                                 blr_neq,
                                    blr_field, 18, 18, 'R','D','B','$','S','E','C','U','R','I','T','Y','_','C','L','A','S','S',
blr_substring,
                                    blr_concatenate,
                                       blr_literal, blr_text, 4,0, 'S','Q','L','$',
                                       blr_field, 18, 18, 'R','D','B','$','P','R','O','C','E','D','U','R','E','_','N','A','M','E',
blr_literal, blr_long, 0, 0,0,0,0,
blr_literal, blr_long, 0, 31,0,0,0,
                                 blr_leave, 3,
                                 blr_end,
                           blr_end,
                     blr_end,
               blr_end,
            blr_eoc
};


static CONST UCHAR FAR_VARIABLE trigger2 [] = 
{
blr_version5,
blr_if, 
   blr_not, 
      blr_missing, 
         blr_field, 0, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E', 
   blr_for, 
      blr_rse, 1, 
         blr_relation, 19, 'R','D','B','$','R','E','L','A','T','I','O','N','_','F','I','E','L','D','S', 3, 
         blr_boolean, 
            blr_and, 
               blr_eql, 
                  blr_field, 3, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E', 
                  blr_field, 0, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E', 
               blr_eql, 
                  blr_field, 3, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E', 
                  blr_field, 0, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E', 
         blr_end, 
      blr_begin, 
         blr_if, 
            blr_starting, 
               blr_field, 3, 18, 'R','D','B','$','S','E','C','U','R','I','T','Y','_','C','L','A','S','S', 
               blr_literal, blr_text, 9,0, 'S','Q','L','$','G','R','A','N','T',
            blr_begin, 
               blr_for, 
                  blr_rse, 1, 
                     blr_relation, 20, 'R','D','B','$','S','E','C','U','R','I','T','Y','_','C','L','A','S','S','E','S', 4, 
                     blr_boolean, 
                        blr_eql, 
                           blr_field, 4, 18, 'R','D','B','$','S','E','C','U','R','I','T','Y','_','C','L','A','S','S', 
                           blr_field, 3, 18, 'R','D','B','$','S','E','C','U','R','I','T','Y','_','C','L','A','S','S', 
                     blr_end, 
                  blr_begin, 
                     blr_erase, 4, 
                     blr_end, 
               blr_modify, 3, 5, 
                  blr_begin, 
                     blr_assignment, 
                        blr_null, 
                        blr_field, 5, 18, 'R','D','B','$','S','E','C','U','R','I','T','Y','_','C','L','A','S','S', 
                     blr_end, 
               blr_end, 
            blr_end, 
         blr_end, 
   blr_end, 
blr_eoc,
};


/******
static CONST TEXT trigger_3_msg_0 [] = "cannot modify an existing user privilege";
******/

static CONST UCHAR trigger3 [] = 
	{
	blr_version5,
	blr_leave, 0, 
	blr_eoc
	};

/******
static CONST TEXT trigger_4_msg_0 [] = "cannot modify or erase a system trigger";
******/

static CONST UCHAR trigger4 [] = 
	{
	blr_version5,
	blr_if, 
	   blr_containing, 
	      blr_field, 0, 16, 'R','D','B','$','T','R','I','G','G','E','R','_','N','A','M','E', 
	      blr_literal, blr_text, 4,0, 'R','D','B','$',
	   blr_leave, 0, 
	   blr_end, 
	blr_eoc
	};

static CONST UCHAR trigger5 [] =
	{
                blr_version5,
                blr_if, 
                   blr_missing, 
                      blr_field, 1, 14, 'R','D','B','$','O','W','N','E','R','_','N','A','M','E', 
                   blr_assignment, 
                      blr_upcase, 
                         blr_user_name, 
                      blr_field, 1, 14, 'R','D','B','$','O','W','N','E','R','_','N','A','M','E', 
                   blr_end, 
                blr_eoc,
	};

/******
static CONST TEXT trigger_6_msg_0 [] = "only the owner of a relation may reassign ownership";
******/

static CONST UCHAR trigger6 [] =
	{
                blr_version5,
                blr_if, 
                   blr_and, 
                      blr_neq, 
                         blr_field, 0, 14, 'R','D','B','$','O','W','N','E','R','_','N','A','M','E', 
                         blr_field, 1, 14, 'R','D','B','$','O','W','N','E','R','_','N','A','M','E', 
                      blr_neq, 
                         blr_field, 0, 14, 'R','D','B','$','O','W','N','E','R','_','N','A','M','E', 
                         blr_upcase, 
                            blr_user_name, 
                   blr_leave, 0, 
                   blr_end, 
                blr_eoc,
	};

static CONST UCHAR trigger7 [] =
	{
                blr_version5,
                blr_assignment, 
                   blr_gen_id, 14, 'R','D','B','$','G','E','N','E','R','A','T','O','R','S',
                      blr_literal, blr_long, 0, 1,0,0,0,
                   blr_field, 1, 16, 'R','D','B','$','G','E','N','E','R','A','T','O','R','_','I','D', 
                blr_eoc,
	};

/* define trigger add_constraint for rdb$relation_constraints  */

/******
static CONST TEXT trigger_26_msg_0 [] = "Cannot define constraints on VIEWS";
static CONST TEXT trigger_26_msg_1 [] = "internal gds software consistency check (Invalid RDB$CONSTRAINT_TYPE)";
static CONST TEXT trigger_26_msg_2 [] = "Attempt to define a second primary key for the same relation";
******/

static CONST UCHAR FAR_VARIABLE trigger26 [] =
        {
                blr_version5,
                blr_begin, 
                   blr_if, 
                      blr_any, 
                         blr_rse, 1, 
                            blr_relation, 13, 'R','D','B','$','R','E','L','A','T','I','O','N','S', 3, 
                            blr_boolean, 
                               blr_and, 
                                  blr_eql, 
                                     blr_field, 3, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E', 
                                     blr_field, 1, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E', 
                                  blr_not, 
                                     blr_missing, 
                                        blr_field, 3, 15, 'R','D','B','$','V','I','E','W','_','S','O','U','R','C','E', 
                            blr_end, 
                      blr_leave, 1, 
                      blr_end, 
                   blr_if, 
                      blr_not, 
                         blr_or, 
                            blr_eql, 
                               blr_field, 1, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                               blr_literal, blr_text, 6,0, 'U','N','I','Q','U','E',
                            blr_or, 
                               blr_eql, 
                                  blr_field, 1, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                                  blr_literal, blr_text, 11,0, 'P','R','I','M','A','R','Y',32,'K','E','Y',
                               blr_or, 
                                  blr_eql, 
                                     blr_field, 1, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                                     blr_literal, blr_text, 11,0, 'F','O','R','E','I','G','N',32,'K','E','Y',
                                  blr_or, 
                                     blr_eql, 
                                        blr_field, 1, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                                        blr_literal, blr_text, 8,0, 'N','O','T',32,'N','U','L','L',
                                     blr_eql, 
                                        blr_field, 1, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                                        blr_literal, blr_text, 5,0, 'C','H','E','C','K',
                      blr_leave, 2, 
                      blr_end, 
                   blr_if, 
                      blr_eql, 
                         blr_field, 1, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                         blr_literal, blr_text, 11,0, 'P','R','I','M','A','R','Y',32,'K','E','Y',
                      blr_begin, 
                         blr_if, 
                            blr_any, 
                               blr_rse, 1, 
                                  blr_relation, 24, 'R','D','B','$','R','E','L','A','T','I','O','N','_','C','O','N','S','T','R','A','I','N','T','S', 4, 
                                  blr_boolean, 
                                     blr_and, 
                                        blr_eql, 
                                           blr_field, 4, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                                           blr_literal, blr_text, 11,0, 'P','R','I','M','A','R','Y',32,'K','E','Y',
                                        blr_eql, 
                                           blr_field, 4, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E', 
                                           blr_field, 1, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E', 
                                  blr_end, 
                            blr_leave, 3, 
                            blr_end, 
                         blr_end, 
                      blr_end, 
                   blr_end, 
                blr_eoc,
	};


/* define trigger update_constraint for rdb$relation_constraints  */

/******
static CONST TEXT trigger_25_msg_0 [] = "Can't update constraints (RDB$RELATION_CONSTRAINTS).";
******/

static CONST UCHAR trigger25 [] =
        {
                blr_version5,
                blr_begin,
                   blr_leave, 1,
                   blr_end,
                blr_eoc,
       };


/* define trigger pre_delete_constraint for rdb$relation_constraints */

/******
static CONST TEXT trigger_10_msg_0 [] = "Cannot delete PRIMARY KEY being used in FOREIGN KEY definition.";
static CONST TEXT trigger_10_msg_1 [] = "Cannot drop NOT NULL constraint for fields in PRIMARY/UNIQUE constraints.";
******/

static CONST UCHAR FAR_VARIABLE trigger10 [] =
        {
                blr_version5,
                blr_begin, 
                   blr_if, 
                      blr_or, 
                         blr_eql, 
                            blr_field, 0, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                            blr_literal, blr_text, 11,0, 'P','R','I','M','A','R','Y',32,'K','E','Y',
                         blr_eql, 
                            blr_field, 0, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                            blr_literal, blr_text, 6,0, 'U','N','I','Q','U','E',
                      blr_begin, 
                         blr_if, 
                            blr_any, 
                               blr_rse, 1, 
                                  blr_relation, 19, 'R','D','B','$','R','E','F','_','C','O','N','S','T','R','A','I','N','T','S', 3, 
                                  blr_boolean, 
                                     blr_eql, 
                                        blr_field, 3, 17, 'R','D','B','$','C','O','N','S','T','_','N','A','M','E','_','U','Q', 
                                        blr_field, 0, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E', 
                                  blr_end, 
                            blr_leave, 1, 
                            blr_end, 
                         blr_end, 
                      blr_end, 
                   blr_if, 
                      blr_eql, 
                         blr_field, 0, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                         blr_literal, blr_text, 11,0, 'F','O','R','E','I','G','N',32,'K','E','Y',
                      blr_begin, 
                         blr_for, 
                            blr_rse, 1, 
                               blr_relation, 19, 'R','D','B','$','R','E','F','_','C','O','N','S','T','R','A','I','N','T','S', 4, 
                               blr_boolean, 
                                  blr_eql, 
                                     blr_field, 0, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E', 
                                     blr_field, 4, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E', 
                               blr_end, 
                            blr_begin, 
                               blr_erase, 4, 
                               blr_end, 
                         blr_end, 
                      blr_end, 
                   blr_if, 
                      blr_eql, 
                         blr_field, 0, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                         blr_literal, blr_text, 8,0, 'N','O','T',32,'N','U','L','L',
                      blr_begin, 
                         blr_for, 
                            blr_rse, 4, 
                               blr_relation, 21, 'R','D','B','$','C','H','E','C','K','_','C','O','N','S','T','R','A','I','N','T','S', 5, 
                               blr_relation, 19, 'R','D','B','$','R','E','L','A','T','I','O','N','_','F','I','E','L','D','S', 6, 
                               blr_relation, 11, 'R','D','B','$','I','N','D','I','C','E','S', 7, 
                               blr_relation, 18, 'R','D','B','$','I','N','D','E','X','_','S','E','G','M','E','N','T','S', 8, 
                               blr_boolean, 
                                  blr_and, 
                                     blr_eql, 
                                        blr_field, 0, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E', 
                                        blr_field, 5, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E', 
                                     blr_and, 
                                        blr_eql, 
                                           blr_field, 6, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E', 
                                           blr_field, 5, 16, 'R','D','B','$','T','R','I','G','G','E','R','_','N','A','M','E', 
                                        blr_and, 
                                           blr_eql, 
                                              blr_field, 6, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E', 
                                              blr_field, 0, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E', 
                                           blr_and, 
                                              blr_eql, 
                                                 blr_field, 6, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E', 
                                                 blr_field, 8, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E', 
                                              blr_and, 
                                                 blr_eql, 
                                                    blr_field, 7, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E', 
                                                    blr_field, 0, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E', 
                                                 blr_eql, 
                                                    blr_field, 7, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E', 
                                                    blr_field, 8, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E', 
                               blr_end, 
                            blr_begin, 
                               blr_if, 
                                  blr_any, 
                                     blr_rse, 1, 
                                        blr_relation, 24, 'R','D','B','$','R','E','L','A','T','I','O','N','_','C','O','N','S','T','R','A','I','N','T','S', 9, 
                                        blr_boolean, 
                                           blr_and, 
                                              blr_eql, 
                                                 blr_field, 9, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E', 
                                                 blr_field, 8, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E', 
                                              blr_or, 
                                                 blr_eql, 
                                                    blr_field, 9, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                                                    blr_literal, blr_text, 6,0, 'U','N','I','Q','U','E',
                                                 blr_eql, 
                                                    blr_field, 9, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                                                    blr_literal, blr_text, 11,0, 'P','R','I','M','A','R','Y',32,'K','E','Y',
                                        blr_end, 
                                  blr_leave, 2, 
                                  blr_end, 
                               blr_end, 
                         blr_end, 
                      blr_end, 
                   blr_end, 
                blr_eoc,
        };

/* define trigger post_delete_constraint for rdb$relation_constraints   */

static CONST UCHAR FAR_VARIABLE trigger11 [] =
        {
            blr_version5,
            blr_begin,
               blr_if,
                  blr_or,
                     blr_eql,
                        blr_field, 0, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E',
                        blr_literal, blr_text, 11,0, 'F','O','R','E','I','G','N',32,'K','E','Y',
                     blr_or,
                        blr_eql,
                           blr_field, 0, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E',
                           blr_literal, blr_text, 11,0, 'P','R','I','M','A','R','Y',32,'K','E','Y',
                        blr_eql,
                           blr_field, 0, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E',
                           blr_literal, blr_text, 6,0, 'U','N','I','Q','U','E',
                  blr_begin,
                     blr_for,
                        blr_rse, 1,
                           blr_relation, 11, 'R','D','B','$','I','N','D','I','C','E','S', 3,
                           blr_boolean,
                              blr_eql,
                                 blr_field, 0, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E',
                                 blr_field, 3, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E',
                           blr_end,
                        blr_begin,
                           blr_erase, 3,
                           blr_for,
                              blr_rse, 1,
                                 blr_relation, 18, 'R','D','B','$','I','N','D','E','X','_','S','E','G','M','E','N','T','S', 4,
                                 blr_boolean,
                                    blr_eql,
                                       blr_field, 4, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E',
                                       blr_field, 3, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E',
                                 blr_end,
                              blr_begin,
                                 blr_erase, 4,
                                 blr_end,
                           blr_end,
                     blr_end,
                  blr_end,
               blr_if,
                  blr_eql,
                     blr_field, 0, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E',
                     blr_literal, blr_text, 8,0, 'N','O','T',32,'N','U','L','L',
                  blr_begin,
                     blr_for,
                        blr_rse, 2,
                           blr_relation, 21, 'R','D','B','$','C','H','E','C','K','_','C','O','N','S','T','R','A','I','N','T','S', 5,
                           blr_relation, 19, 'R','D','B','$','R','E','L','A','T','I','O','N','_','F','I','E','L','D','S', 6,
                           blr_boolean,
                              blr_and,
                                 blr_eql,
                                    blr_field, 0, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E',
                                    blr_field, 5, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E',
                                 blr_and,
                                    blr_eql,
                                       blr_field, 6, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                       blr_field, 0, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                    blr_eql,
                                       blr_field, 6, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E',
                                       blr_field, 5, 16, 'R','D','B','$','T','R','I','G','G','E','R','_','N','A','M','E',
                           blr_end,
                        blr_begin,
                           blr_erase, 5,
                           blr_modify, 6, 7,
                              blr_begin,
                                 blr_assignment,
                                    blr_literal, blr_long, 0, 0,0,0,0,
                                    blr_field, 7, 13, 'R','D','B','$','N','U','L','L','_','F','L','A','G',
                                 blr_end,
                           blr_end,
                     blr_end,
                  blr_end,
               blr_if,
                  blr_eql,
                     blr_field, 0, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E',
                     blr_literal, blr_text, 5,0, 'C','H','E','C','K',
                  blr_begin,
                     blr_for,
                        blr_rse, 1,
                           blr_relation, 21, 'R','D','B','$','C','H','E','C','K','_','C','O','N','S','T','R','A','I','N','T','S', 8,
                           blr_boolean,
                              blr_eql,
                                 blr_field, 0, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E',
                                 blr_field, 8, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E',
                           blr_end,
                        blr_begin,
                           blr_erase, 8,
                           blr_for,
                              blr_rse, 1,
                                 blr_relation, 12, 'R','D','B','$','T','R','I','G','G','E','R','S', 9,
                                 blr_boolean,
                                    blr_and,
                                       blr_eql,
                                          blr_field, 9, 16, 'R','D','B','$','T','R','I','G','G','E','R','_','N','A','M','E',
                                          blr_field, 8, 16, 'R','D','B','$','T','R','I','G','G','E','R','_','N','A','M','E',
                                       blr_eql,
                                          blr_field, 9, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                          blr_field, 0, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                 blr_end,
                              blr_begin,
                                 blr_erase, 9,
                                 blr_end,
                           blr_end,
                     blr_end,
                  blr_end,
               blr_end,
            blr_eoc
        };

/* define trigger add_ref_constraint for rdb$ref_constraints  */

/******
static CONST TEXT trigger_12_msg_0 [] = "Name of Referential Constraint not defined in constraints relation.";
static CONST TEXT trigger_12_msg_1 [] = "Non-existent Primary or Unique key specifed for Foreign Key.";
******/

static CONST UCHAR FAR_VARIABLE trigger12 [] =
        {
                blr_version5,
                blr_begin, 
                   blr_if, 
                      blr_not, 
                         blr_any, 
                            blr_rse, 1, 
                               blr_relation, 24, 'R','D','B','$','R','E','L','A','T','I','O','N','_','C','O','N','S','T','R','A','I','N','T','S', 3, 
                               blr_boolean, 
                                  blr_and, 
                                     blr_eql, 
                                        blr_field, 3, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E', 
                                        blr_field, 1, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E', 
                                     blr_eql, 
                                        blr_field, 3, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                                        blr_literal, blr_text, 11,0, 'F','O','R','E','I','G','N',32,'K','E','Y',
                               blr_end, 
                      blr_leave, 1, 
                      blr_end, 
                   blr_if, 
                      blr_not, 
                         blr_any, 
                            blr_rse, 1, 
                               blr_relation, 24, 'R','D','B','$','R','E','L','A','T','I','O','N','_','C','O','N','S','T','R','A','I','N','T','S', 4, 
                               blr_boolean, 
                                  blr_and, 
                                     blr_eql, 
                                        blr_field, 4, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E', 
                                        blr_field, 1, 17, 'R','D','B','$','C','O','N','S','T','_','N','A','M','E','_','U','Q', 
                                     blr_or, 
                                        blr_eql, 
                                           blr_field, 4, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                                           blr_literal, blr_text, 11,0, 'P','R','I','M','A','R','Y',32,'K','E','Y',
                                        blr_eql, 
                                           blr_field, 4, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                                           blr_literal, blr_text, 6,0, 'U','N','I','Q','U','E',
                               blr_end, 
                      blr_leave, 2, 
                      blr_end, 
                   blr_end, 
                blr_eoc,
       };

/* define trigger update_ref_constraint for rdb$ref_constraints */

/******
static CONST TEXT trigger_13_msg_0 [] = "Can't update constraints (RDB$REF_CONSTRAINTS).";
******/

static CONST UCHAR trigger13 [] =
        {
                blr_version5,
                blr_begin,
                   blr_leave, 1,
                   blr_end,
                blr_eoc,
       };

/* define trigger update_check_constraint for rdb$check_constraints */

/******
static CONST TEXT trigger_14_msg_0 [] = "Can't update constraints (RDB$CHECK_CONSTRAINTS).";
******/

static CONST UCHAR trigger14 [] =
        {
                blr_version5,
                blr_begin,
                   blr_leave, 1,
                   blr_end,
                blr_eoc,
       };

/* define trigger pre_delete_check_constraint for rdb$check_constraints */

/******
static CONST TEXT trigger_15_msg_0 [] = "Can't delete CHECK constraint entry (RDB$CHECK_CONSTRAINTS)";
******/

static CONST UCHAR trigger15 [] =
        {
                blr_version5,
                blr_begin, 
                   blr_if, 
                      blr_any,
                         blr_rse, 1,
                            blr_relation, 24, 'R','D','B','$','R','E','L','A','T','I','O','N','_','C','O','N','S','T','R','A','I','N','T','S', 3,
                            blr_boolean,
                               blr_eql,
                                  blr_field, 3, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E',
                                  blr_field, 0, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E',
                            blr_end,
                      blr_leave, 1,
                      blr_end,
                   blr_end,
                blr_eoc,

       };

/* define trigger post_delete_check_constraint for rdb$check_constraints */

static CONST UCHAR FAR_VARIABLE trigger16 [] =
        {
            blr_version5,
            blr_begin,
               blr_for,
                  blr_rse, 2,
                     blr_relation, 19, 'R','D','B','$','R','E','L','A','T','I','O','N','_','F','I','E','L','D','S', 3,
                     blr_relation, 24, 'R','D','B','$','R','E','L','A','T','I','O','N','_','C','O','N','S','T','R','A','I','N','T','S', 4,
                     blr_boolean,
                        blr_and,
                           blr_eql,
                              blr_field, 3, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                              blr_field, 4, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                           blr_and,
                              blr_eql,
                                 blr_field, 4, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E',
                                 blr_field, 0, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E',
                              blr_and,
                                 blr_eql,
                                    blr_field, 4, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E',
                                    blr_literal, blr_text, 8,0, 'N','O','T',32,'N','U','L','L',
                                 blr_eql,
                                    blr_field, 3, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E',
                                    blr_field, 0, 16, 'R','D','B','$','T','R','I','G','G','E','R','_','N','A','M','E',
                     blr_end,
                  blr_begin,
                     blr_modify, 3, 5,
                        blr_begin,
                           blr_assignment,
                              blr_literal, blr_long, 0, 0,0,0,0,
                              blr_field, 5, 13, 'R','D','B','$','N','U','L','L','_','F','L','A','G',
                           blr_end,
                     blr_end,
               blr_for,
                  blr_rse, 2,
                     blr_relation, 12, 'R','D','B','$','T','R','I','G','G','E','R','S', 6,
                     blr_relation, 24, 'R','D','B','$','R','E','L','A','T','I','O','N','_','C','O','N','S','T','R','A','I','N','T','S', 7,
                     blr_boolean,
                        blr_and,
                           blr_eql,
                              blr_field, 7, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E',
                              blr_field, 0, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E',
                           blr_and,
                              blr_eql,
                                 blr_field, 7, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E',
                                 blr_literal, blr_text, 5,0, 'C','H','E','C','K',
                              blr_and,
                                 blr_eql,
                                    blr_field, 6, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                    blr_field, 7, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                 blr_eql,
                                    blr_field, 6, 16, 'R','D','B','$','T','R','I','G','G','E','R','_','N','A','M','E',
                                    blr_field, 0, 16, 'R','D','B','$','T','R','I','G','G','E','R','_','N','A','M','E',
                     blr_end,
                  blr_begin,
                     blr_erase, 6,
                     blr_end,
               blr_end,
            blr_eoc
        };

/* define trigger delete_constraint_segs for rdb$index_segments  */

/******
static CONST TEXT trigger_17_msg_0 [] = "Can't delete index segment used by an Integrity Constraint";
******/

static CONST UCHAR trigger17 [] =
        {
                blr_version5,
                blr_begin, 
                   blr_if, 
                      blr_any, 
                         blr_rse, 1, 
                            blr_relation, 24, 'R','D','B','$','R','E','L','A','T','I','O','N','_','C','O','N','S','T','R','A','I','N','T','S', 3, 
                            blr_boolean, 
                               blr_eql, 
                                  blr_field, 3, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E', 
                                  blr_field, 0, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E', 
                            blr_end, 
                      blr_leave, 1, 
                      blr_end, 
                   blr_end, 
                blr_eoc,
       };

/* define trigger update_constraint_segs for rdb$index_segments  */

/******
static CONST TEXT trigger_18_msg_0 [] = "Can't update index segment used by an Integrity Constraint";
******/

static CONST UCHAR trigger18 [] =
        {
                blr_version5,
                blr_begin, 
                   blr_if, 
                      blr_any, 
                         blr_rse, 1, 
                            blr_relation, 24, 'R','D','B','$','R','E','L','A','T','I','O','N','_','C','O','N','S','T','R','A','I','N','T','S', 3, 
                            blr_boolean, 
                               blr_eql, 
                                  blr_field, 3, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E', 
                                  blr_field, 0, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E', 
                            blr_end, 
                      blr_leave, 1, 
                      blr_end, 
                   blr_end, 
                blr_eoc,
       };

/* define trigger delete_constraint_idx for rdb$indices  */

/******
static CONST TEXT trigger_19_msg_0 [] = "Can't delete index used by an Integrity Constraint";
******/

static CONST UCHAR trigger19 [] =
        {
                blr_version5,
                blr_begin, 
                   blr_if, 
                      blr_any, 
                         blr_rse, 1, 
                            blr_relation, 24, 'R','D','B','$','R','E','L','A','T','I','O','N','_','C','O','N','S','T','R','A','I','N','T','S', 3, 
                            blr_boolean, 
                               blr_eql, 
                                  blr_field, 3, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E', 
                                  blr_field, 0, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E', 
                            blr_end, 
                      blr_leave, 1, 
                      blr_end, 
                   blr_end, 
                blr_eoc,
       };

/* define trigger update_constraint_idx for rdb$indices  */

/******
static CONST TEXT trigger_20_msg_0 [] = "Can't modify index used by an Integrity Constraint";
static CONST TEXT trigger_20_msg_1 [] = "Can't deactivate index used by an Integrity Constraint";
static CONST TEXT trigger_20_msg_2 [] = "Can't deactivate a primary index";
******/

static CONST UCHAR FAR_VARIABLE trigger20 [] =
        {
            blr_version5,
            blr_begin,
               blr_if,
                  blr_any,
                     blr_rse, 1,
                        blr_relation, 24, 'R','D','B','$','R','E','L','A','T','I','O','N','_','C','O','N','S','T','R','A','I','N','T','S', 3,
                        blr_boolean,
                           blr_eql,
                              blr_field, 3, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E',
                              blr_field, 0, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E',
                        blr_end,
                  blr_begin,
                     blr_if,
                        blr_not,
                           blr_and,
                              blr_eql,
                                 blr_field, 0, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E',
                                 blr_field, 1, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E',
                              blr_and,
                                 blr_eql,
                                    blr_field, 0, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                    blr_field, 1, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                 blr_and,
                                    blr_eql,
                                       blr_field, 0, 12, 'R','D','B','$','I','N','D','E','X','_','I','D',
                                       blr_field, 1, 12, 'R','D','B','$','I','N','D','E','X','_','I','D',
                                    blr_and,
                                       blr_eql,
                                          blr_field, 0, 17, 'R','D','B','$','S','E','G','M','E','N','T','_','C','O','U','N','T',
                                          blr_field, 1, 17, 'R','D','B','$','S','E','G','M','E','N','T','_','C','O','U','N','T',
                                       blr_eql,
                                          blr_field, 0, 15, 'R','D','B','$','F','O','R','E','I','G','N','_','K','E','Y',
                                          blr_field, 1, 15, 'R','D','B','$','F','O','R','E','I','G','N','_','K','E','Y',
                        blr_leave, 1,
                        blr_end,
                     blr_end,
                  blr_end,
               blr_for,
                  blr_rse, 3,
                     blr_relation, 24, 'R','D','B','$','R','E','L','A','T','I','O','N','_','C','O','N','S','T','R','A','I','N','T','S', 4,
                     blr_relation, 11, 'R','D','B','$','I','N','D','I','C','E','S', 5,
                     blr_relation, 11, 'R','D','B','$','I','N','D','I','C','E','S', 6,
                     blr_boolean,
                        blr_and,
                           blr_eql,
                              blr_field, 4, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E',
                              blr_field, 0, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E',
                           blr_and,
                              blr_eql,
                                 blr_field, 5, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E',
                                 blr_field, 0, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E',
                              blr_and,
                                 blr_eql,
                                    blr_field, 6, 15, 'R','D','B','$','F','O','R','E','I','G','N','_','K','E','Y',
                                    blr_field, 0, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E',
                                 blr_and,
                                    blr_eql,
                                       blr_field, 1, 18, 'R','D','B','$','I','N','D','E','X','_','I','N','A','C','T','I','V','E',
                                       blr_literal, blr_long, 0, 1,0,0,0,
                                    blr_or,
                                       blr_eql,
                                          blr_field, 0, 18, 'R','D','B','$','I','N','D','E','X','_','I','N','A','C','T','I','V','E',
                                          blr_literal, blr_long, 0, 0,0,0,0,
                                       blr_missing,
                                          blr_field, 0, 18, 'R','D','B','$','I','N','D','E','X','_','I','N','A','C','T','I','V','E',
                     blr_end,
                  blr_begin,
                     blr_leave, 2,
                     blr_end,
               blr_if,
                  blr_any,
                     blr_rse, 1,
                        blr_relation, 24, 'R','D','B','$','R','E','L','A','T','I','O','N','_','C','O','N','S','T','R','A','I','N','T','S', 7,
                        blr_boolean,
                           blr_and,
                              blr_eql,
                                 blr_field, 7, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E',
                                 blr_field, 0, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E',
                              blr_or,
                                 blr_eql,
                                    blr_field, 7, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E',
                                    blr_literal, blr_text, 11,0, 'P','R','I','M','A','R','Y',32,'K','E','Y',
                                 blr_eql,
                                    blr_field, 7, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E',
                                    blr_literal, blr_text, 11,0, 'F','O','R','E','I','G','N',32,'K','E','Y',
                        blr_end,
                  blr_begin,
                     blr_if,
                        blr_and,
                           blr_eql,
                              blr_field, 1, 18, 'R','D','B','$','I','N','D','E','X','_','I','N','A','C','T','I','V','E',
                              blr_literal, blr_long, 0, 1,0,0,0,
                           blr_or,
                              blr_eql,
                                 blr_field, 0, 18, 'R','D','B','$','I','N','D','E','X','_','I','N','A','C','T','I','V','E',
                                 blr_literal, blr_long, 0, 0,0,0,0,
                              blr_missing,
                                 blr_field, 0, 18, 'R','D','B','$','I','N','D','E','X','_','I','N','A','C','T','I','V','E',
                        blr_leave, 3,
                        blr_end,
                     blr_end,
                  blr_end,
               blr_end,
            blr_eoc
       };

/* define trigger delete_constraint_trigger for rdb$triggers  */

/******
static CONST TEXT trigger_21_msg_0 [] = "Can't delete trigger used by a CHECK Constraint";
******/

static CONST UCHAR trigger21 [] =
        {
                blr_version5,
                blr_begin, 
                   blr_for, 
                      blr_rse, 2, 
                         blr_relation, 21, 'R','D','B','$','C','H','E','C','K','_','C','O','N','S','T','R','A','I','N','T','S', 3, 
                         blr_relation, 24, 'R','D','B','$','R','E','L','A','T','I','O','N','_','C','O','N','S','T','R','A','I','N','T','S', 4, 
                         blr_boolean, 
                            blr_and, 
                               blr_eql, 
                                  blr_field, 3, 16, 'R','D','B','$','T','R','I','G','G','E','R','_','N','A','M','E', 
                                  blr_field, 0, 16, 'R','D','B','$','T','R','I','G','G','E','R','_','N','A','M','E', 
                               blr_and, 
                                  blr_eql, 
                                     blr_field, 4, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E', 
                                     blr_field, 3, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E', 
                                  blr_eql, 
                                     blr_field, 4, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                                     blr_literal, blr_text, 5,0, 'C','H','E','C','K',
                         blr_end, 
                      blr_begin, 
                         blr_leave, 1, 
                         blr_end, 
                   blr_end, 
                blr_eoc,
        };

/* define trigger update_constraint_trigger for rdb$triggers  */

/******
static CONST TEXT trigger_22_msg_0 [] = "Can't update trigger used by a CHECK Constraint";
******/

static CONST UCHAR trigger22 [] =
        {
                blr_version5,
                blr_begin, 
                   blr_for, 
                      blr_rse, 2, 
                         blr_relation, 21, 'R','D','B','$','C','H','E','C','K','_','C','O','N','S','T','R','A','I','N','T','S', 3, 
                         blr_relation, 24, 'R','D','B','$','R','E','L','A','T','I','O','N','_','C','O','N','S','T','R','A','I','N','T','S', 4, 
                         blr_boolean, 
                            blr_and, 
                               blr_eql, 
                                  blr_field, 3, 16, 'R','D','B','$','T','R','I','G','G','E','R','_','N','A','M','E', 
                                  blr_field, 0, 16, 'R','D','B','$','T','R','I','G','G','E','R','_','N','A','M','E', 
                               blr_and, 
                                  blr_eql, 
                                     blr_field, 4, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E', 
                                     blr_field, 3, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E', 
                                  blr_eql, 
                                     blr_field, 4, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                                     blr_literal, blr_text, 5,0, 'C','H','E','C','K',
                         blr_end, 
                      blr_begin, 
                         blr_leave, 1, 
                         blr_end, 
                   blr_end, 
                blr_eoc,
        };

/* define trigger pre_delete_field for rdb$relation_fields  */

/******
static CONST TEXT trigger_23_msg_0 [] = "Cannot delete field being used in an integrity constraint.";
******/

static CONST UCHAR FAR_VARIABLE trigger23 [] =
        {
                blr_version5,
                blr_begin, 
                   blr_for, 
                      blr_rse, 3, 
                         blr_relation, 11, 'R','D','B','$','I','N','D','I','C','E','S', 3, 
                         blr_relation, 24, 'R','D','B','$','R','E','L','A','T','I','O','N','_','C','O','N','S','T','R','A','I','N','T','S', 4, 
                         blr_relation, 18, 'R','D','B','$','I','N','D','E','X','_','S','E','G','M','E','N','T','S', 5, 
                         blr_boolean, 
                            blr_and, 
                               blr_eql, 
                                  blr_field, 3, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E', 
                                  blr_field, 0, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E', 
                               blr_and, 
                                  blr_eql, 
                                     blr_field, 3, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E', 
                                     blr_field, 5, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E', 
                                  blr_and, 
                                     blr_eql, 
                                        blr_field, 4, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E', 
                                        blr_field, 5, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E', 
                                     blr_and, 
                                        blr_eql, 
                                           blr_field, 5, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E', 
                                           blr_field, 0, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E', 
                                        blr_or, 
                                           blr_eql, 
                                              blr_field, 4, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                                              blr_literal, blr_text, 6,0, 'U','N','I','Q','U','E',
                                           blr_or, 
                                              blr_eql, 
                                                 blr_field, 4, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                                                 blr_literal, blr_text, 11,0, 'F','O','R','E','I','G','N',32,'K','E','Y',
                                              blr_eql, 
                                                 blr_field, 4, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                                                 blr_literal, blr_text, 11,0, 'P','R','I','M','A','R','Y',32,'K','E','Y',
                         blr_end, 
                      blr_begin, 
                         blr_if, 
                            blr_any, 
                               blr_rse, 1, 
                                  blr_relation, 18, 'R','D','B','$','I','N','D','E','X','_','S','E','G','M','E','N','T','S', 6, 
                                  blr_boolean, 
                                     blr_and, 
                                        blr_eql, 
                                           blr_field, 6, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E', 
                                           blr_field, 5, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E', 
                                        blr_neq, 
                                           blr_field, 6, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E', 
                                           blr_field, 0, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E', 
                                  blr_end, 
                            blr_leave, 1, 
                            blr_erase, 4, 
                         blr_end, 
                   blr_end, 
                blr_eoc,
       };

/* define trigger pre_modify_field for rdb$relation_fields  */

/******
static CONST TEXT trigger_24_msg_0 [] = "Cannot rename field being used in an integrity constraint.";
******/

static CONST UCHAR FAR_VARIABLE trigger24 [] =
        {
                blr_version5,
                blr_begin, 
                   blr_if, 
                      blr_neq, 
                         blr_field, 0, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E', 
                         blr_field, 1, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E', 
                      blr_for, 
                         blr_rse, 3, 
                            blr_relation, 11, 'R','D','B','$','I','N','D','I','C','E','S', 3, 
                            blr_relation, 24, 'R','D','B','$','R','E','L','A','T','I','O','N','_','C','O','N','S','T','R','A','I','N','T','S', 4, 
                            blr_relation, 18, 'R','D','B','$','I','N','D','E','X','_','S','E','G','M','E','N','T','S', 5, 
                            blr_boolean, 
                               blr_and, 
                                  blr_eql, 
                                     blr_field, 3, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E', 
                                     blr_field, 0, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E', 
                                  blr_and, 
                                     blr_eql, 
                                        blr_field, 3, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E', 
                                        blr_field, 5, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E', 
                                     blr_and, 
                                        blr_eql, 
                                           blr_field, 4, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E', 
                                           blr_field, 5, 14, 'R','D','B','$','I','N','D','E','X','_','N','A','M','E', 
                                        blr_and, 
                                           blr_eql, 
                                              blr_field, 5, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E', 
                                              blr_field, 0, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E', 
                                           blr_or, 
                                              blr_eql, 
                                                 blr_field, 4, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                                                 blr_literal, blr_text, 6,0, 'U','N','I','Q','U','E',
                                              blr_or, 
                                                 blr_eql, 
                                                    blr_field, 4, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                                                    blr_literal, blr_text, 11,0, 'F','O','R','E','I','G','N',32,'K','E','Y',
                                                 blr_eql, 
                                                    blr_field, 4, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                                                    blr_literal, blr_text, 11,0, 'P','R','I','M','A','R','Y',32,'K','E','Y',
                            blr_end, 
                         blr_begin, 
                            blr_leave, 1, 
                            blr_end, 
                      blr_end, 
                   blr_end, 
                blr_eoc,
       };


/* define trigger post_delete_field for rdb$relation_fields  */
static CONST UCHAR trigger27 [] =
        {
                blr_version5,
                blr_begin, 
                   blr_for, 
                      blr_rse, 2, 
                         blr_relation, 21, 'R','D','B','$','C','H','E','C','K','_','C','O','N','S','T','R','A','I','N','T','S', 3, 
                         blr_relation, 24, 'R','D','B','$','R','E','L','A','T','I','O','N','_','C','O','N','S','T','R','A','I','N','T','S', 4, 
                         blr_boolean, 
                            blr_and, 
                               blr_eql, 
                                  blr_field, 0, 14, 'R','D','B','$','F','I','E','L','D','_','N','A','M','E', 
                                  blr_field, 3, 16, 'R','D','B','$','T','R','I','G','G','E','R','_','N','A','M','E', 
                               blr_and, 
                                  blr_eql, 
                                     blr_field, 4, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E', 
                                     blr_field, 3, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E', 
                                  blr_and, 
                                     blr_eql, 
                                        blr_field, 0, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E', 
                                        blr_field, 4, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E', 
                                     blr_eql, 
                                        blr_field, 4, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E', 
                                        blr_literal, blr_text, 8,0, 'N','O','T',32,'N','U','L','L',
                         blr_end, 
                      blr_begin, 
                         blr_erase, 4, 
                         blr_erase, 3, 
                         blr_end, 
                   blr_end, 
                blr_eoc,
        };

static CONST UCHAR trigger28 [] =
       {
blr_version5,
blr_begin, 
   blr_if, 
      blr_missing, 
         blr_field, 1, 14, 'R','D','B','$','O','W','N','E','R','_','N','A','M','E', 
      blr_assignment, 
         blr_upcase, 
            blr_user_name, 
         blr_field, 1, 14, 'R','D','B','$','O','W','N','E','R','_','N','A','M','E', 
      blr_end, 
   blr_assignment, 
      blr_gen_id, 14, 'R','D','B','$','P','R','O','C','E','D','U','R','E','S',
         blr_literal, blr_long, 0, 1,0,0,0,
      blr_field, 1, 16, 'R','D','B','$','P','R','O','C','E','D','U','R','E','_','I','D', 
   blr_end, 
blr_eoc
	};

static CONST UCHAR trigger29 [] =
       {
		blr_version5,
		blr_if,
		   blr_and,
		      blr_neq,
			 blr_field, 0, 14, 'R','D','B','$','O','W','N','E','R','_','N','A','M','E',
		         blr_field, 1, 14, 'R','D','B','$','O','W','N','E','R','_','N','A','M','E',
		      blr_neq,
			 blr_field, 0, 14, 'R','D','B','$','O','W','N','E','R','_','N','A','M','E',
			 blr_upcase,
			    blr_user_name,
		   blr_leave, 0,
		   blr_end,
	        blr_eoc
	};

static CONST UCHAR trigger30 [] =
       {
blr_version5,
blr_begin, 
   blr_assignment, 
      blr_gen_id, 14, 'R','D','B','$','E','X','C','E','P','T','I','O','N','S',
         blr_literal, blr_long, 0, 1,0,0,0,
      blr_field, 1, 20, 'R','D','B','$','E','X','C','E','P','T','I','O','N','_','N','U','M','B','E','R', 
   blr_end, 
blr_eoc
	};


/* new trigger to create ODS 8.1 (and to upgrade from ODS 8.0 to ODS 8.1 */
static CONST UCHAR trigger31 [] = 
	{
            blr_version5,
            blr_begin,
               blr_if,
                  blr_and,
                     blr_not,
                        blr_missing,
                           blr_field, 1, 11, 'R','D','B','$','G','R','A','N','T','O','R',
                     blr_and,
                        blr_neq,
                           blr_field, 1, 11, 'R','D','B','$','G','R','A','N','T','O','R',
                           blr_upcase,
                              blr_user_name,
                        blr_neq,
                           blr_upcase,
                              blr_user_name,
                           blr_literal, blr_text, 6,0, 'S','Y','S','D','B','A',
                  blr_begin,
                     blr_for,
                        blr_rse, 1,
                           blr_relation, 13, 'R','D','B','$','R','E','L','A','T','I','O','N','S', 3,
                           blr_boolean,
                              blr_eql,
                                 blr_field, 3, 17, 'R','D','B','$','R','E','L','A','T','I','O','N','_','N','A','M','E',
                                 blr_literal, blr_text, 12,0, 'R','D','B','$','D','A','T','A','B','A','S','E',
                           blr_end,
                        blr_begin,
                           blr_if,
                              blr_or,
                                 blr_missing,
                                    blr_field, 3, 14, 'R','D','B','$','O','W','N','E','R','_','N','A','M','E',
                                 blr_neq,
                                    blr_field, 3, 14, 'R','D','B','$','O','W','N','E','R','_','N','A','M','E',
                                    blr_upcase,
                                       blr_user_name,
                              blr_leave, 0,
                              blr_end,
                           blr_end,
                     blr_end,
                  blr_end,
               blr_end,
            blr_eoc
        };


/* ODS 8.1 trigger  */
static CONST UCHAR trigger34 [] = 
	{
            blr_version5,
            blr_begin,
               blr_if,
                  blr_eql,
                     blr_field, 0, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E',
                     blr_literal, blr_text, 11,0, 'F','O','R','E','I','G','N',32,'K','E','Y',
                  blr_begin,
                     blr_for,
                        blr_rse, 1,
                           blr_relation, 21, 'R','D','B','$','C','H','E','C','K','_','C','O','N','S','T','R','A','I','N','T','S', 3,
                           blr_boolean,
                              blr_eql,
                                 blr_field, 0, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E',
                                 blr_field, 3, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E',
                           blr_end,
                        blr_begin,
                           blr_erase, 3,
                           blr_for,
                              blr_rse, 1,
                                 blr_relation, 12, 'R','D','B','$','T','R','I','G','G','E','R','S', 4,
                                 blr_boolean,
                                    blr_eql,
                                       blr_field, 4, 16, 'R','D','B','$','T','R','I','G','G','E','R','_','N','A','M','E',
                                       blr_field, 3, 16, 'R','D','B','$','T','R','I','G','G','E','R','_','N','A','M','E',
                                 blr_end,
                              blr_begin,
                                 blr_erase, 4,
                                 blr_end,
                           blr_end,
                     blr_end,
                  blr_end,
               blr_end,
            blr_eoc
	};

/* ODS 8.1 trigger  */
static CONST UCHAR trigger35 [] = 
	{
            blr_version5,
            blr_begin,
               blr_for,
                  blr_rse, 2,
                     blr_relation, 12, 'R','D','B','$','T','R','I','G','G','E','R','S', 3,
                     blr_relation, 24, 'R','D','B','$','R','E','L','A','T','I','O','N','_','C','O','N','S','T','R','A','I','N','T','S', 4,
                     blr_boolean,
                        blr_and,
                           blr_eql,
                              blr_field, 4, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E',
                              blr_field, 0, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','N','A','M','E',
                           blr_and,
                              blr_eql,
                                 blr_field, 4, 19, 'R','D','B','$','C','O','N','S','T','R','A','I','N','T','_','T','Y','P','E',
                                 blr_literal, blr_text, 11,0, 'F','O','R','E','I','G','N',32,'K','E','Y',
                              blr_eql,
                                 blr_field, 3, 16, 'R','D','B','$','T','R','I','G','G','E','R','_','N','A','M','E',
                                 blr_field, 0, 16, 'R','D','B','$','T','R','I','G','G','E','R','_','N','A','M','E',
                     blr_end,
                  blr_begin,
                     blr_erase, 3,
                     blr_end,
               blr_end,
            blr_eoc
	};

#endif /* _JRD_TRIG_H_ */
