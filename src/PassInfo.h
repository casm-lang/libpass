//  
//  Copyright (c) 2015-2016 Philipp Paulweber
//  All rights reserved.
//  
//  Developed by: Philipp Paulweber
//                https://github.com/ppaulweber/libpass
//  
//  This file is part of libpass.
//  
//  libpass is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  libpass is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with libpass. If not, see <http://www.gnu.org/licenses/>.
//  

#ifndef _LIB_PASS_PASSINFO_H_
#define _LIB_PASS_PASSINFO_H_

#include "Type.h"

/**
   @brief    TODO
   
   TODO
*/

namespace libpass
{
    class PassInfo
    {
    private:
        const char* const name;
        const char* const description;
        const char* const arg_str;
        const char        arg_char;
    
        const PassId  id;
    
        PassConstructor constructor;
    
        uint64_t changes;

    public:
        PassInfo
        ( const char* passName
        , const char* passDescription
        , const char* passArgStr
        , const char  passArgChar
        , const PassId passID
        , PassConstructor passConstructor
        )
        : name( passName )
        , description( passDescription )
        , arg_str( passArgStr )
        , arg_char( passArgChar )
        , id( passID )
        , constructor( passConstructor )
        {
        }
        
        const char* getPassName(void) const 
        { 
            return name; 
        }
    
        const char* getPassDescription(void) const 
        { 
            return description; 
        }
    
        const char* getPassArgString(void) const 
        { 
            return arg_str; 
        }
    
        const char getPassArgChar(void) const 
        { 
            return arg_char; 
        }
    
        const PassId getPassId(void) const
        {
            return id;
        }

        bool isPassID(const PassId passID) const
        {
            return passID == id;
        }
    
        void addChanges(uint64_t change)
        {
            changes += change;
        }
    
        uint64_t getChanges(void)
        {
            return changes;
        }
    
        Pass* constructPass(void) const
        {
            return constructor();
        }
    
        friend ostream& operator<<(ostream& os, PassInfo& pi)
        {
            return os; // << pi.getPassName() << ": ";
        }
    };
}

#endif /* _LIB_PASS_PASSINFO_H_ */


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
