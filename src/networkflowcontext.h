#ifndef _SF_NET_FLOW_
#define _SF_NET_FLOW_
#include <ctime>
#include "datatypes.h"
#include <sinsp.h>
#include "op_flags.h"
#include "sysflowcontext.h"
#include "sysflowwriter.h"
#include "processcontext.h"
#include "sysflow/sysflow.hh"
#define NF_TABLE_SIZE 50000
using namespace sysflow;
namespace networkflow {


    class NetworkFlowContext {
        private:
            SysFlowContext* m_cxt;
            process::ProcessContext* m_processCxt;
            SysFlowWriter* m_writer;
            //NetworkFlowTable m_netflows;
            NetworkFlowSet m_nfSet;
            OIDNetworkTable m_oidnfTable;
            NFKey m_nfdelkey;
            NFKey m_nfemptykey;
            OID m_oiddelkey;
            OID m_oidemptykey;
            time_t m_lastCheck;
            void canonicalizeKey(sinsp_fdinfo_t* fdinfo, NFKey* key);
            void canonicalizeKey(NetFlowObj* nf, NFKey* key);
            void populateNetFlow(NetFlowObj* nf, NFOpFlags flag, sinsp_evt* ev, Process* proc);
            void updateNetFlow(NetFlowObj* nf, NFOpFlags flag, sinsp_evt* ev);
            void processExistingFlow(sinsp_evt* ev, Process* proc, NFOpFlags flag, NFKey key, NetFlowObj* nf);
            void processNewFlow(sinsp_evt* ev, Process* proc, NFOpFlags flag, NFKey key) ;
            void removeAndWriteNetworkFlow(NetFlowObj** nf, NFKey* key);
            void removeNetworkFlow(NetFlowObj** nf, NFKey* key);
         
            time_t getExportTime();
            int32_t getProtocol(scap_l4_proto proto);
            NetworkFlowTable* createNetworkFlowTable();
        public:
            NetworkFlowContext(SysFlowContext* cxt, SysFlowWriter* writer, process::ProcessContext* procCxt);
            virtual ~NetworkFlowContext();
            int handleNetFlowEvent(sinsp_evt* ev, NFOpFlags flag);
            void clearNetFlows();
            int checkForExpiredFlows();
            inline int getSize() {
                int total = 0;
                for(OIDNetworkTable::iterator it = m_oidnfTable.begin(); it != m_oidnfTable.end(); it++) {
                     total+= it->second->size();
                 }
                return total;
            }
            int removeAndWriteNFFromProc(OID* oid);
            
         
    };
}
#endif
