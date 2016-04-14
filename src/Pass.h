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
//  along with this program. If not, see <http://www.gnu.org/licenses/>.
//  

#ifndef _LIB_PASS_PASS_H_
#define _LIB_PASS_PASS_H_

#include "PassInfo.h"
#include "PassUsage.h"
#include "PassResult.h"
#include "PassRegistry.h"

/**
   @brief    TODO
   
   TODO
*/

namespace libpass
{
	class PassUsage;
	class PassResult;

	class Pass  
	{
	public:
		virtual void usage(PassUsage& pu)
		{
		}
	
		virtual void initialize(void)
		{
		}
	
		virtual bool run(PassResult& pr) = 0;
	
		virtual bool verify(void)
		{
			return true;
		}
	
		virtual void finalize(void)
		{
		}	
	
		virtual void dealloc(void* result)
		{
		}	
	};
}

#endif /* _LIB_PASS_PASS_H_ */


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
