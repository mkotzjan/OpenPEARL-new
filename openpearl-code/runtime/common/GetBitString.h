/*
 [A "BSD license"]
 Copyright (c) 2012-2013 Rainer Mueller
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
 3. The name of the author may not be used to endorse or promote products
    derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
\file

\brief get-formatting of types BIT(x)

\author R. Mueller

This module contains the input formatting von BitStrings
for B1,B2,B3 and B4-format.
*/

#ifndef GETBITSTRING_H_INCLUDED
#define GETBITSTRING_H_INCLUDED


#include "Source.h"
#include "GetHelper.h"
#include "Signals.h"

using namespace std;
namespace pearlrt {
   /**
   \addtogroup io_common_helper
   @{
   */

   /**
   \brief Input formatting of bit string variables.

   \tparam S the length of the BitString
   */
   template<int S> class GetBitString {
   private:
      /**
       no constructor needed, since the only static methods
       are provided. They need no objects.
      */
      GetBitString() {}
   public:

      /**
      convert the bit string from a character stream in bin-format.

      The bit value is expected to be in an input field of width w.
      The input field must not be empty.
      Leading or trailing spaces are ignored.

      If less bits are given in the input, the remaining bits are
      padded at the right side with 0.

      If more bits are given as the variable may store, the leftmost
      bits are considered. The other bits are discarded quietly.

      If w == 0: the value 0 is assigned to the input variable

      \param bitstring the data to be read
      \param w the width of the input field.
      \param base is 1 (B1), 2(B2) or 3(B3)-format
      \param source the origin of the character sequence
      \throws  BitFormatSignal  if w is < 0, or <br>
      \throws  BitValueSignal if field was empty
      */
      static void fromB123(
         BitString<S> &bitstring,
         const Fixed<31> w,
         const int base,
         Source & source) {
         if (w.x < 0) {
            throw theBitFormatSignal;
         }

         if (w.x == 0) {
            bitstring.x = 0;
            return;
         }

         GetHelper helper(w, &source);
         helper.setDelimiters(GetHelper::EndOfLine);
         uint64_t fixedValue = 0;
        
         helper.readB123(&fixedValue, S, base);
         BitString<S> retVal(fixedValue);
         bitstring.x = retVal.x;
         return;
      }


      /**
      convert the bit string from a character stream in hex-format.

      The bit value is expected to be in an input field of width w.
      The input field must not be empty.
      Leading or trailing spaces are ignored.

      If less bits are given in the input, the remaining bits are
      padded at the right side with 0.

      If more bits are given as the variable may store, the leftmost
      bits are considered. The other bits are discarded quietly.

      If w == 0: the value 0 is assigned to the input variable

      \param bitstring the data to be read
      \param w the width of the input field.
      \param source the origin of the character sequence
      \throws BitFormatSignal if w is < 0, or <br>
      \throws BitValueSignal if field was empty
      */
      static void fromB4(
         BitString<S> &bitstring,
         const Fixed<31> w,
         Source & source) {
         if (w.x < 0) {
            throw theBitFormatSignal;
         }

         if (w.x == 0) {
            bitstring.x = 0;
            return;
         }

         GetHelper helper(w, &source);
         helper.setDelimiters(GetHelper::EndOfLine);
         uint64_t fixedValue=0;
         helper.readB4(&fixedValue, S);
         BitString<S> retVal(fixedValue);
         bitstring.x = retVal.x;
         return;
      }

   };
   /** @} */
}
#endif

