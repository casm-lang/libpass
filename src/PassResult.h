
/*
  Copyright (C) 2015 Philipp Paulweber
  
  This file is part of the 'libpass' project which is released under a NSCA
  open source software license. For more information, see the LICENSE.txt
  file in the project root directory.
*/

#ifndef _LIB_PASS_PASSRESULT_H_
#define _LIB_PASS_PASSRESULT_H_

#include "Type.h"

/**
   @file     PassResult.h
   @class    PassResult
   
   @brief    TODO
   
   TODO
   
   @author   Philipp Paulweber
   @date     2015-02-14
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
	
		/**
		   @brief    TODO

		   TODO
	   
		   @param    arg0    TODO
		   @return   TODO
		   @retval   TODO
		*/
	
		template<class PassName>
		void* getResult(void)
		{
			//DEBUG( __FUNCTION__ << ": " << &PassName::id << " = " << results[ &PassName::id ] 
			//<< "\n" );
		
			return results[ &PassName::id ];
		}
	
		template<class PassName>
		void setResult(void* passResult)
		{
			//DEBUG( __FUNCTION__ << ": " << &PassName::id << " = " << passResult << "\n" );
		
			results[ &PassName::id ] = passResult;
		}
	
		PassId2Ptr& getResults(void)
		{
			return results;
		}
	
		void printAllResults(void)
		{
			// DEBUG( __FUNCTION__ << ": " << results.size() << "\n" );
		
			// for( auto& r : results )
			// {
			// 	DEBUG( __FUNCTION__ << ": " << r.first << " = " << r.second << "\n" );
			// }
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


/*
  Local variables:
  mode: c++
  indent-tabs-mode: t
  c-basic-offset: 4
  tab-width: 4
  End:
  vim:noexpandtab:sw=4:ts=4:
*/
