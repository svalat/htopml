/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_HWLOC_THREAD_BINDING_HTTP_NODE_H
#define HTOPML_HWLOC_THREAD_BINDING_HTTP_NODE_H

/********************  HEADERS  *********************/
#include <vector>
#include <hwloc.h>
#include "JsonHttpNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  STRUCT  *********************/
struct HwlocThreadBinding
{
	//static members
	int threadId;
	std::string binding;
	std::string lastPosition;
};

/*********************  STRUCT  *********************/
typedef std::vector<HwlocThreadBinding> HwlocThreadBindingVector;

/*********************  STRUCT  *********************/
struct HwlocBinding
{
	HwlocThreadBindingVector threads;
	std::string binding;
	int processId;
};

/*******************  FUNCTION  *********************/
void typeToJson(JsonState & state,std::ostream& stream,const HwlocThreadBinding & value);
void typeToJson(JsonState & state,std::ostream& stream,const HwlocBinding & value);

/*********************  CLASS  **********************/
class HwlocThreadBindingHttpNode : public JsonHttpNode<HwlocBinding>
{
	public:
		HwlocThreadBindingHttpNode(const std::string& path);
		virtual ~HwlocThreadBindingHttpNode(void );
		virtual void onRequest(const HttpRequest& request);
	private:
		void initHwloc(void);
		void syncListOfThreads(void);
		void syncHwlocInfos(void);
		std::string getBindingFromCpuset(hwloc_bitmap_t cpuset, bool show_cpuset, bool logical = true);
		hwloc_obj_t getDeepestUniqChild(hwloc_obj_t  obj);
	private:
		bool hwlocWasInit;
		HwlocBinding data;
		hwloc_topology_t topology;
		hwloc_const_bitmap_t topocpuset;
		hwloc_bitmap_t cpuset;
};

}

#endif // HTOPML_HWLOC_THREAD_BINDING_HTTP_NODE_H
