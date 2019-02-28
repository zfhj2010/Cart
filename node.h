class node
{
public:
    node();
    node(int feature, double value, node* leftnode, node* m_rightnode);
    int getfeature();
    void setfeature(int feature);
    double getvalue();
    void setvalue(double value);
    node* getleftnode();
    node* getrightnode();
private:
    int m_feature;
    double m_value;
    node* m_leftnode;
    node* m_rightnode;
};