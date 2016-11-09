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
        const PassId  id;
        const char* const name;
        const char* const description;
        PassConstructor constructor;
        
        const char* const arg_str;
        const char        arg_char;
        function< void( const char* ) > arg_action;
        bool arg_selected;
        
        uint64_t changes;

    public:
        PassInfo
        ( const PassId passID
        , const char*  passName
        , const char*  passDescription
        , PassConstructor passConstructor
        , const char* passArgStr
        , const char  passArgChar
        , function< void( const char* ) > passArgAction
        )
        : id( passID )
        , name( passName )
        , description( passDescription )
        , constructor( passConstructor )
        , arg_str( passArgStr )
        , arg_char( passArgChar )
        , arg_action( passArgAction )
        , arg_selected( false )
        , changes( 0 )
        {
        }
        
        PassInfo
        ( const PassId passID
        , const char*  passName
        , const char*  passDescription
        , PassConstructor passConstructor
        , const char* passArgStr
        , const char  passArgChar
        )
        : id( passID )
        , name( passName )
        , description( passDescription )
        , constructor( passConstructor )
        , arg_str( passArgStr )
        , arg_char( passArgChar )
        , arg_selected( false )
        , changes( 0 )
        {
            arg_action = [ this ]( const char* arg )
            {
                this->arg_selected = true;
            };
        }
        
        const PassId getPassId(void) const
        {
            return id;
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

        const function< void( const char* ) >& getPassArgAction(void) const 
        { 
            return arg_action; 
        }
        
        const bool isPassArgSelected(void) const 
        { 
            return arg_selected; 
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
            Pass* p = constructor();

            assert( p and "unable to create pass" );
            
            return p;
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
