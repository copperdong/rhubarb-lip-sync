/*************************************************************************/
/*                                                                       */
/*                  Language Technologies Institute                      */
/*                     Carnegie Mellon University                        */
/*                        Copyright (c) 2004                             */
/*                        All Rights Reserved.                           */
/*                                                                       */
/*  Permission is hereby granted, free of charge, to use and distribute  */
/*  this software and its documentation without restriction, including   */
/*  without limitation the rights to use, copy, modify, merge, publish,  */
/*  distribute, sublicense, and/or sell copies of this work, and to      */
/*  permit persons to whom this work is furnished to do so, subject to   */
/*  the following conditions:                                            */
/*   1. The code must retain the above copyright notice, this list of    */
/*      conditions and the following disclaimer.                         */
/*   2. Any modifications must be clearly marked as such.                */
/*   3. Original authors' names are not deleted.                         */
/*   4. The authors' names are not used to endorse or promote products   */
/*      derived from this software without specific prior written        */
/*      permission.                                                      */
/*                                                                       */
/*  CARNEGIE MELLON UNIVERSITY AND THE CONTRIBUTORS TO THIS WORK         */
/*  DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING      */
/*  ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT   */
/*  SHALL CARNEGIE MELLON UNIVERSITY NOR THE CONTRIBUTORS BE LIABLE      */
/*  FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES    */
/*  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN   */
/*  AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,          */
/*  ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF       */
/*  THIS SOFTWARE.                                                       */
/*                                                                       */
/*************************************************************************/
/*             Author:  Alan W Black (awb@cs.cmu.edu)                    */
/*               Date:  December 2004                                    */
/*************************************************************************/
/*                                                                       */
/*  PalmOS Callbacks to System Functions                                 */
/*                                                                       */
/*************************************************************************/
#include <PalmOS.h>
#include <PceNativeCall.h>
#include <CoreTraps.h>
#include <FileStream.h>
#include "pocore.h"

Int32 FileReadLow(FileHand stream, void *baseP, Int32 offset, 
		  Boolean dataStoreBased, Int32 objSize,
		  Int32 numObj, Err *errP)
{
    Int32 r;
    unsigned char stack[28];

    *(int *)&stack[0] = SWAPINT(stream);
    *(int *)&stack[4] = SWAPINT(baseP);
    *(int *)&stack[8] = SWAPINT(offset);
    *(int *)&stack[12] = SWAPINT(dataStoreBased);
    *(int *)&stack[16] = SWAPINT(objSize);
    *(int *)&stack[20] = SWAPINT(numObj);
    *(int *)&stack[24] = SWAPINT(errP);

    r = (Int32)(*gCall68KFuncP)(gEmulStateP,
				PceNativeTrapNo(sysTrapFileReadLow),
				stack,
				28 | kPceNativeWantA0);
    return r;
}





