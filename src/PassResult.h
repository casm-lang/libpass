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

#ifndef _LIB_PASS_PASSRESULT_H_
#define _LIB_PASS_PASSRESULT_H_

#include "Type.h"

/**
   @brief    TODO
   
   TODO
*/

namespace libpass
{
	class PassResult  
	{
	private:
	
		PassId2Ptr results;
	
		PassId2u64 changes;
	
	public:
		PassResult()
		{
		}
	
		~PassResult()
		{
			results.clear();
			changes.clear();
		}
	
		template<class PassName>
		void* getResult(void)
		{
			return results[ &PassName::id ];
		}
	
		template<class PassName>
		void setResult(void* passResult)
		{
			results[ &PassName::id ] = passResult;
		}
	
		PassId2Ptr& getResults(void)
		{
			return results;
		}
	
		void printAllResults(void)
		{
		}
	
		uint64_t getChanges(PassId id)
		{
			return changes[ id ];
		}
	
		template<class PassName>
		void setChanges(uint64_t passChanges)
		{
			changes[ &PassName::id ] = passChanges;
		
			if( passChanges > 0 )
			{
			} 
		}
	
		void setChanges(PassId id, uint64_t passChanges)
		{
			changes[ id ] = passChanges;
		}
	
		friend ostream& operator<<(ostream& os, PassResult& pr)
		{
			return os;
		}	
	};
}

#endif /* _LIB_PASS_PASSRESULT_H_ */


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
