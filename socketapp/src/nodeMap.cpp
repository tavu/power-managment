#include"nodeMap.h"
using namespace std;
node* nodeMap::addNode(node* n)
{
    ipMap[n->ip()]=n;
    macMap[n->mac()]=n;

    return n;
}

node* nodeMap::nodeFromIp(string ip)
{
    map<string,node*>::iterator it=ipMap.find(ip);
    if(it==ipMap.end() )
    {
        return 0;
    }
    return it->second;
}

node* nodeMap::nodeFromMac(string mac)
{
    map<string,node*>::iterator it=macMap.find(mac);
    if(it==macMap.end() )
    {
        return 0;
    }
    return it->second;
}

nodeMap* nMap()
{
    return nodeMap::_nmap;
}

nodeMap* nodeMap::_nmap=0;
