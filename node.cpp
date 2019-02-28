#include "node.h"

node::node()
{

}

node::node(int feature, double value, node* leftnode, node* m_rightnode)
{
    m_feature = feature;
    m_value = value;
    m_leftnode = leftnode;
    m_rightnode = m_rightnode;
}

int node::getfeature()
{
    return m_feature;
}
    
void node::setfeature(int feature)
{
    m_feature = feature;
}
    
double node::getvalue()
{
    return m_value;
}
    
void node::setvalue(double value)
{
    m_value = value;
}
    
node* node::getleftnode()
{
    return m_leftnode;
}
    
node* node::getrightnode()
{
    return m_rightnode;
}