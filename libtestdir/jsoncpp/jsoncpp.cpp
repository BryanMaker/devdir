#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <fstream>
#include <iostream>

void printNode(Json::Value v);
void print(Json::Value v);
int main()
{
    std::ifstream filein("../custom_real_coco_jq.json");

    if (!filein.is_open())
    {
        std::cout << "open json file failed" << std::endl;
        return -1;
    }

    Json::Reader reader;
    Json::Value root;

    // 从文件流读取根节点 
    if (!reader.parse(filein, root))
    {
        std::cout << "read json file failed" << std::endl;
        return -1;
    }

    printNode(root);

    Json::Value::Members mem_root = root.getMemberNames();
    /*
     * annotations # 标签的标注信息
     * categories # 类别id与类别名的列号
     * images # 图片id与图片文件名映射
     */
    /*
    auto iter_annotations = mem_root.begin();
    std::cout << *iter_annotations << std::endl;
    auto iter_categories = mem_root.begin() + 1;
    std::cout << *iter_categories << std::endl;
    auto iter_images = mem_root.begin() + 2;
    std::cout << *iter_images << std::endl;
    */


    /*
    for (auto iter_root = mem_root.begin(); iter_root != mem_root.end(); iter_root++)
    {
        std::cout << *iter_root << std::endl;
        continue;
        if (root[*iter_root].type() == Json::objectValue)
        {
            Json::Value::Members mem_child = root[*iter_root].getMemberNames();
            for (auto iter_chlid = mem_child.begin(); iter_chlid != mem_child.end(); iter_chlid++)
            {
                std::cout << "\t" << *iter_chlid << std::endl;
            }
        }

        if (root[*iter_root].type() == Json::arrayValue)
        {
            unsigned int cnt = root[*iter_root].size();
            std::cout << "size: " << cnt << std::endl;
            for (unsigned int i = 0; i < cnt; i++)
            {
                Json::Value::Members mem_child = root[*iter_root][i].getMemberNames();
                for (auto iter_chelid = mem_child.begin(); iter_chelid != mem_child.end(); iter_chelid++)
                {
                    std::cout << "\t" << *iter_chelid << std::endl;
                }
            }
        }
    }
    */

    return 0;
}

void printNode(Json::Value v)
    {
    Json::Value::Members mem = v.getMemberNames();

    for (auto iter = mem.begin(); iter != mem.end(); iter++) // 遍历传入节点的子节点
    {
        std::cout << *iter << std::endl;

        if (v[*iter].type() == Json::objectValue) // 当前子节点是可遍历的节点
        {
            printNode(v[*iter]); // 遍历该子节点的子节点
        }
        else if (v[*iter].type() == Json::arrayValue) // 当前子节点是可遍历的节点集合
        {
            unsigned int cnt = v[*iter].size(); // 获取节点个数
            for (unsigned int i = 0; i < cnt; i++)
            {
                printNode(v[*iter][i]); // 分别遍历该集合中的节点
            }
        }
        else
        {
            print(v[*iter]);
        }
    }
}

void print(Json::Value v)
{
    if (v.type() == Json::stringValue) // 当前节点是string类型值
    {
        std::cout << v.asString() << std::endl;
    }
    else if (v.type() == Json::realValue)
    {
        std::cout << v.asDouble() << std::endl;
    }
    else if (v.type() == Json::uintValue)
    {
        std::cout << v.asUInt() << std::endl;
    }
    else
    {
        std::cout << v.asInt() << std::endl;
    }
}
