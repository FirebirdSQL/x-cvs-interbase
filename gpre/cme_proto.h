/*
 *	PROGRAM:	Preprocessor
 *	MODULE:		cme_proto.h
 *	DESCRIPTION:	Prototype header file for cme.c
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

#ifndef _GPRE_CME_PROTO_H_
#define _GPRE_CME_PROTO_H_

extern void	CME_expr (NOD, REQ);
extern void	CME_get_dtype (NOD, FLD);
extern void	CME_relation (CTX, REQ);
extern void	CME_rse (RSE, REQ);

#endif /* _GPRE_CME_PROTO_H_ */
