#ifndef NODE_MAP_H
#define NODE_MAP_H

#include<string>
#include<map>
#include"node.h"
#include<pthread.h>



class nodeMap
{
    public:
        friend nodeMap* nMap();

        nodeMap()
        {
            handsh=false;
            pthread_mutex_init(&mutex, NULL);
        }

        ~nodeMap()
        {
            pthread_mutex_destroy(&mutex);
        }


        node* addNode(node* n);
        node* nodeFromIp(std::string ip);
        node* nodeFromMac(std::string mac);

        bool  hasHandSh()
        {
            return handsh;
        }

        void setHandSh(bool b)
        {
            handsh=b;
        }

        int size()
        {
            return ipMap.size();
        }

        typedef std::map<std::string,node*>::iterator nodeIter;

        nodeIter ipBegin()
        {
            return ipMap.begin();
        }

        nodeIter ipEnd()
        {
            return ipMap.end();
        }

        node* nodeFromIt(nodeIter &it)
        {
            return it->second;
        }

        void lock()
        {
            pthread_mutex_lock(&mutex);
        }

        void unlock()
        {
            pthread_mutex_unlock(&mutex);
        }

        static void init()
        {
            _nmap=new nodeMap();
        }
        
        void delete_node(node* n)
	{
	  ipMap.erase(n->ip());
	  macMap.erase(n->mac());
	}
	 
        static void clear()
        {
            delete _nmap;
            _nmap=0;
        }

    private:
        pthread_mutex_t mutex;
        bool handsh;
        std::map<std::string,node*> ipMap;
        std::map<std::string,node*> macMap;

        static nodeMap* _nmap;
};

nodeMap* nMap();

#endif
