/*
 *	PROGRAM:	InterBase International support
 *	MODULE:		lc_jis.c
 *	DESCRIPTION:	Language Drivers in the JIS family.
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


#include "../intl/ldcommon.h"
#include "../jrd/license.h"


extern USHORT	famasc_key_length();
extern USHORT	famasc_string_to_key();
extern SSHORT	famasc_compare();
extern USHORT	famasc_to_upper();
extern USHORT	famasc_to_lower();
extern SSHORT	famasc_str_to_upper();
static USHORT	sjis_to_upper();
static USHORT	sjis_to_lower();
static SSHORT	sjis_str_to_upper();
extern USHORT	CVJIS_sjis_byte2short();
extern USHORT	CVJIS_euc_byte2short();
extern SSHORT	CVJIS_sjis_mbtowc();
extern SSHORT	CVJIS_euc_mbtowc();


#define FAMILY_MULTIBYTE(id_number, name, charset, country) \
	cache->texttype_version =		IB_LANGDRV_VERSION; \
	cache->texttype_type =			(id_number); \
	cache->texttype_character_set =		(charset); \
	cache->texttype_country =		(country); \
	cache->texttype_bytes_per_char =	2; \
	cache->texttype_fn_init =		(name); \
	cache->texttype_fn_key_length =		famasc_key_length; \
	cache->texttype_fn_string_to_key =	famasc_string_to_key; \
	cache->texttype_fn_compare =		famasc_compare; \
	cache->texttype_collation_table =	(BYTE *) NULL; \
	cache->texttype_toupper_table =		(BYTE *) NULL; \
	cache->texttype_tolower_table =		(BYTE *) NULL; \
	cache->texttype_compress_table =	(BYTE *) NULL; \
	cache->texttype_expand_table =		(BYTE *) NULL; \
	cache->texttype_name =			POSIX; 


TEXTTYPE_ENTRY (JIS220_init)
{
static CONST ASCII	POSIX[] = "C.SJIS";

FAMILY_MULTIBYTE (220, JIS220_init, CS_SJIS, CC_C);
cache->texttype_fn_to_wc = CVJIS_sjis_byte2short;
cache->texttype_fn_mbtowc = CVJIS_sjis_mbtowc;

cache->texttype_fn_to_upper =		sjis_to_upper; 
cache->texttype_fn_to_lower =		sjis_to_lower;
cache->texttype_fn_str_to_upper =	sjis_str_to_upper;

TEXTTYPE_RETURN;
}
#include "../intl/undef.h"

TEXTTYPE_ENTRY (JIS230_init)
{
static CONST ASCII	POSIX[] = "C.EUC_J";

FAMILY_MULTIBYTE (230, JIS230_init, CS_EUCJ, CC_C);
cache->texttype_fn_to_wc = CVJIS_euc_byte2short;
cache->texttype_fn_mbtowc = CVJIS_euc_mbtowc;

cache->texttype_fn_to_upper =		famasc_to_upper;
cache->texttype_fn_to_lower =		famasc_to_lower;
cache->texttype_fn_str_to_upper =	famasc_str_to_upper;

TEXTTYPE_RETURN;
}
#include "../intl/undef.h"


#undef FAMILY_MULTIBYTE



#define ASCII_LOWER_A	'a'
#define ASCII_UPPER_A	'A'
#define ASCII_LOWER_Z	'z'
#define ASCII_UPPER_Z	'Z'

/*
 *	Note: This function expects Wide-Char input, not
 *	Multibyte input
 */
STATIC	USHORT	sjis_to_upper (obj, ch)
TEXTTYPE	obj;
WCHAR		ch;
{
if (ch >= (WCHAR) ASCII_LOWER_A && ch <= (WCHAR) ASCII_LOWER_Z)
    return (ch - (WCHAR) ASCII_LOWER_A + (WCHAR) ASCII_UPPER_A);
return ch;
}


/*
 *	Returns -1 if output buffer was too small
 */
/*
 *	Note: This function expects Multibyte input
 */
STATIC	SSHORT	sjis_str_to_upper (obj, iLen, pStr, iOutLen, pOutStr)
TEXTTYPE	obj;
USHORT		iLen;
BYTE		*pStr;
USHORT		iOutLen;
BYTE		*pOutStr;
{
BYTE	*p;
USHORT	waiting_for_sjis2 = FALSE;
BYTE	c;

assert (pStr != NULL);
assert (pOutStr != NULL);
assert (iLen <= 32000);		/* almost certainly an error */
assert (iOutLen <= 32000);	/* almost certainly an error */
assert (iOutLen >= iLen);
p = pOutStr;
while (iLen && iOutLen) 
    {
    c = *pStr++;
    if (waiting_for_sjis2 || SJIS1 (c))
	{
	waiting_for_sjis2 = !waiting_for_sjis2;
	}
    else
	{
	if (c >= ASCII_LOWER_A && c <= ASCII_LOWER_Z)
    	    c = (c - ASCII_LOWER_A + ASCII_UPPER_A);
	}
    *pOutStr++ = c;
    iLen--;
    iOutLen--;
    }
if (iLen != 0)
    return (-1);		/* Must have ran out of output space */
return (pOutStr - p);
}



/*
 *	Note: This function expects Wide-Char input, not
 *	Multibyte input
 */
STATIC	USHORT	sjis_to_lower (obj, ch)
TEXTTYPE	obj;
WCHAR		ch;
{
if (ch >= (WCHAR) ASCII_UPPER_A && ch <= (WCHAR) ASCII_UPPER_Z)
    return (ch - (WCHAR) ASCII_UPPER_A + (WCHAR) ASCII_LOWER_A);
return ch;
}

