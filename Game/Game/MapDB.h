#pragma once
#include <unordered_map>
#include <vector>

enum class ItemType;
enum class ObjectType;
class MapDB
{
	class MapInfo
	{
	public:
		int index = 0;
		ObjectType objectType = ObjectType::None;
		ItemType itemType = ItemType::None;
        std::vector<float> itemheight[2];
	};

public:
    ~MapDB()
    {
        for (MapInfo* info : infos)
            delete info;
    }

	//List<MapInfo*> infos;
    std::vector<MapInfo*> infos;

    void Load(const char* name)
    {
        // ���� �н� ����.
        char path[512] = {};
        strcat_s(path, "../Assets/DB/");
        strcat_s(path, name);
        strcat_s(path, ".txt");

        // ���� ����.
        FILE* file = nullptr;
        fopen_s(&file, path, "r");

        // ���� ó��.
        if (!file)
        {
            std::cout << "DB ���� ���� ����.\n";
            __debugbreak;
            return;
        }

        // �� ���� ����Ʈ �ʱ�ȭ.
        //infos = List<MapInfo*>();

        // �� �پ� �б�
        char line[512];  // �� ���� ������ ����
        while (fgets(line, sizeof(line), file))
        {
            // �� ���� ���� ���� ����
            line[strcspn(line, "\n")] = '\0';

            // �� ���� ���� ����.
            MapInfo* info = new MapInfo();
            int index = 0;

            // ','�� �и�
            char* context = nullptr;
            char* token = strtok_s(line, ",", &context);
            while (token)
            {
                ++index;
                switch (index)
                {
                case 1:
                    info->index = atoi(token);
                    break;
                case 2:
                    if (token)
                    {
                        std::string inputStr(token);
                        info->itemType = stringToItem(inputStr);
                    }
                    else
                        info->itemType = ItemType::None;
                    break;
                case 3:
                {
                    // �� ��° ��: ������ Height ����
                    int i = 0;

                    // token ������ ���� ������ ���۷� ���� (������ �κ�)
                    char buffer[512];
                    strcpy_s(buffer, sizeof(buffer), token);

                    char* tempContext = nullptr; // ������ context ���
                    char* value01 = strtok_s(buffer, "-", &tempContext); // ���纻���� �Ľ�
                    while (value01)
                    {
                        value01[strcspn(value01, "\r\n")] = '\0'; // ���� ����

                        if (strchr(value01, '/'))
                        {
                            char* tempSubContext = nullptr; // ������ ���� context ���
                            char* value02 = strtok_s(value01, "/", &tempSubContext); // '/'�� �߰� �и�
                            while (value02)
                            {
                                value02[strcspn(value02, "\r\n")] = '\0'; // ���� ����

                                double v = atof(value02);
                                if (v != 0)
                                    info->itemheight[i].push_back((float)v);

                                value02 = strtok_s(nullptr, "/", &tempSubContext);
                            }
                        }
                        else
                        {
                            double v = atof(value01);
                            if (v != 0)
                                info->itemheight[i].push_back((float)v);
                        }

                        value01 = strtok_s(nullptr, "-", &tempContext); // ���� '-' ��
                        ++i;
                    }
                }
                    break;
                case 4:
                    if (token != nullptr)
                    {
                        std::string inputStr(token);
                        info->objectType = stringToObject(inputStr);
                    }
                    else
                        info->objectType = ObjectType::None;
                    break;
                }
                token = strtok_s(nullptr, ",", &context);
            }

            // ����Ʈ�� ����
            infos.push_back(info);
        }

        // ���� �ݱ�
        fclose(file);
    }

	ItemType stringToItem(const std::string& str)
	{
		// ���ڿ��� enum ���� �����ϴ� ���̺�
		static const std::unordered_map<std::string, ItemType> itemMap = 
		{
			{"None", ItemType::None},
			{"Coin", ItemType::Coin},
			{"Jelly", ItemType::Jelly},
			{"BearJelly", ItemType::BearJelly},
			{"KingBearJelly", ItemType::KingBearJelly},
			{"Big", ItemType::Big}
		};

		// ���ڿ��� ���̺� �����ϸ� �ش� enum �� ��ȯ, ������ Unknown ��ȯ
		auto it = itemMap.find(str);
		return (it != itemMap.end()) ? it->second : ItemType::None;
	}

	ObjectType stringToObject(const std::string& str)
	{
		// ���ڿ��� enum ���� �����ϴ� ���̺�
		static const std::unordered_map<std::string, ObjectType> objectMap =
		{
			{"None", ObjectType::None},
			{"TopLong01", ObjectType::TopLong01},
			{"TopLong02", ObjectType::TopLong02},
			{"BottomLong01", ObjectType::BottomLong01},
			{"BottomLong02", ObjectType::BottomLong02},
			{"BottomNormal01", ObjectType::BottomNormal01},
			{"BottomNormal02", ObjectType::BottomNormal02}
		};

		// ���ڿ��� ���̺� �����ϸ� �ش� enum �� ��ȯ, ������ Unknown ��ȯ
		auto it = objectMap.find(str);
		return (it != objectMap.end()) ? it->second : ObjectType::None;
	}
};