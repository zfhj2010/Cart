#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include "node.h"

using namespace std;

list<list<double> > loaddata(string file_name)
{
    fstream fs(file_name.c_str(), ios::in);
    list<list<double> > data_set;
    if(fs.is_open())
    {
        while(!fs.eof())
        {
            char line[1024] = {0};
            fs.getline(line, 1024);
            if(fs.eof())break;
            if(line[strlen(line) - 1] == '\r')line[strlen(line) - 1] = '\0';
            vector<string> split_word;
            list<double> item;
            boost::split(split_word, line, boost::is_any_of("\t"), boost::token_compress_on);
            for(int i = 0; i < split_word.size(); i++)
            {
                double data = boost::lexical_cast<double>(split_word[i]);
                item.push_back(data);
            }
            data_set.push_back(item);
        }
    }
    return data_set;
}

void divide_dataset(list<list<double> > dataset, list<list<double> >& train_dataset, list<list<double> >& test_dataset, double proportion)
{
    train_dataset.clear();
    test_dataset.clear();
    srand(time(NULL));
    int* id_list = new int[dataset.size()];
    for(int i = 0; i < dataset.size(); i++)id_list[i] = i;
    int length = dataset.size();
    unsigned int train_length = (int)(length * proportion);
    list<list<double> >::iterator iter;
    for(int i = 0; i < train_length; i++)
    {
        int id = rand() % length;
        length--;
        iter = dataset.begin();
        if(id_list[id] > 0)
        {
            advance(iter, id_list[id] - 1);
        }
        id_list[id] = id_list[length];
        list<double> item = *iter;
        train_dataset.push_back(item);
        cout << endl;
    }
    for(int i = 0; i < length; i++)
    {
        iter = dataset.begin();
        if(id_list[i] > 0)
        {
            advance(iter, id_list[i] - 1);
        }
        list<double> item = *iter;
        test_dataset.push_back(item);
    }
}

void clear_list(list<list<double> > datalist)
{
    list<list<double> >::iterator iter = datalist.begin();
    list<list<double> >::iterator tmpiter;
    for(;iter != datalist.end();)
    {
        tmpiter = iter;
        iter++;
        tmpiter->clear();
    }
    datalist.clear();
}

double compute_mean(list<list<double> > datalist)
{
    double mean = 0;
    list<list<double> >::iterator iter = datalist.begin();
    for(;iter != datalist.end();)
    {
        list<double> item = *iter;
        list<double>::iterator in_iter = item.end();
        in_iter --;
        mean += *in_iter;
    }
    mean /= datalist.size();
    return mean;
}

double compute_error(list<list<double> > datalist)
{
    double var = 0;
    double mean = compute_mean(datalist);
    list<list<double> >::iterator iter = datalist.begin();
    for(;iter != datalist.end();)
    {
        list<double> item = *iter;
        list<double>::iterator in_iter = item.end();
        in_iter --;
        var += pow(*in_iter - mean, 2);
    }
    return var;
}

void divide_dataset(list<list<double> > datalist, int feature, double value, list<list<double> >& leftlist, list<list<double> >& rightlist)
{
    leftlist.clear();
    rightlist.clear();
    list<list<double> >::iterator iter = datalist.begin();
    for(;iter != datalist.end();)
    {
        list<double> item = *iter;
        list<double>::iterator in_iter = item.begin();
        advance(in_iter, feature - 1);
        if(*in_iter > value)
        {
            leftlist.push_back(item);
        }
        else
        {
            rightlist.push_back(item);
        }
        iter++;
    }
}

pair<int, double> select_best_partition(list<list<double> > datalist)
{
    pair<int, double> partition;
    int feature = 0;
    double value = 0;
    double err = 0;
    double minerr = 0;
    err = compute_error(datalist);
    int featurelen = datalist.begin()->size() - 1;
    list<list<double> >::iterator iter = datalist.begin();
    for(int i = 0; i < featurelen; i++)
    {
        for(;iter != datalist.end();)
        {
            list<double>::iterator in_iter = iter->begin();
            advance(in_iter, i);
            list<list<double> > leftlist, rightlist;
            divide_dataset(datalist, i, *in_iter, leftlist, rightlist);
        }
    }
    
    

    return partition;
}

node* construct_tree(list<list<double> > datalist)
{
    select_best_partition(datalist);
    return NULL;
}

int main()
{
    list<list<double> > all_dataset = loaddata("dataset//airfoil_self_noise.txt");
    list<list<double> >train_dataset;
    list<list<double> >test_dataset;
    divide_dataset(all_dataset, train_dataset, test_dataset, 0.8);

    // list<list<double> >::iterator out_iter;
    // list<double>::iterator in_iter;
    // int line_num = 1;
    // for(out_iter = test_dataset.begin(); out_iter != test_dataset.end();)
    // {
    //     list<double> item = *out_iter;
    //     cout << line_num << "\t";
    //     for(in_iter = item.begin();in_iter != item.end();)
    //     {
    //         cout << *in_iter << "\t";
    //         in_iter++;
    //     }
    //     cout << endl;
    //     line_num++;
    //     out_iter++;
    // }
    return 0;
}