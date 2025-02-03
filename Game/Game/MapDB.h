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
        // 파일 패스 지정.
        char path[512] = {};
        strcat_s(path, "../Assets/DB/");
        strcat_s(path, name);
        strcat_s(path, ".txt");

        // 파일 열기.
        FILE* file = nullptr;
        fopen_s(&file, path, "r");

        // 파일 처리.
        if (!file)
        {
            std::cout << "DB 파일 열기 실패.\n";
            __debugbreak;
            return;
        }

        // 맵 정보 리스트 초기화.
        //infos = List<MapInfo*>();

        // 한 줄씩 읽기
        char line[512];  // 한 줄을 저장할 버퍼
        while (fgets(line, sizeof(line), file))
        {
            // 줄 끝의 개행 문자 제거
            line[strcspn(line, "\n")] = '\0';

            // 맵 정보 변수 생성.
            MapInfo* info = new MapInfo();
            int index = 0;

            // ','로 분리
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
                    // 세 번째 값: 아이템 Height 저장
                    int i = 0;

                    // token 내용을 수정 가능한 버퍼로 복사 (수정된 부분)
                    char buffer[512];
                    strcpy_s(buffer, sizeof(buffer), token);

                    char* tempContext = nullptr; // 별도의 context 사용
                    char* value01 = strtok_s(buffer, "-", &tempContext); // 복사본으로 파싱
                    while (value01)
                    {
                        value01[strcspn(value01, "\r\n")] = '\0'; // 개행 제거

                        if (strchr(value01, '/'))
                        {
                            char* tempSubContext = nullptr; // 별도의 하위 context 사용
                            char* value02 = strtok_s(value01, "/", &tempSubContext); // '/'로 추가 분리
                            while (value02)
                            {
                                value02[strcspn(value02, "\r\n")] = '\0'; // 개행 제거

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

                        value01 = strtok_s(nullptr, "-", &tempContext); // 다음 '-' 값
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

            // 리스트에 저장
            infos.push_back(info);
        }

        // 파일 닫기
        fclose(file);
    }

	ItemType stringToItem(const std::string& str)
	{
		// 문자열과 enum 값을 매핑하는 테이블
		static const std::unordered_map<std::string, ItemType> itemMap = 
		{
			{"None", ItemType::None},
			{"Coin", ItemType::Coin},
			{"Jelly", ItemType::Jelly},
			{"BearJelly", ItemType::BearJelly},
			{"KingBearJelly", ItemType::KingBearJelly},
			{"Big", ItemType::Big}
		};

		// 문자열이 테이블에 존재하면 해당 enum 값 반환, 없으면 Unknown 반환
		auto it = itemMap.find(str);
		return (it != itemMap.end()) ? it->second : ItemType::None;
	}

	ObjectType stringToObject(const std::string& str)
	{
		// 문자열과 enum 값을 매핑하는 테이블
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

		// 문자열이 테이블에 존재하면 해당 enum 값 반환, 없으면 Unknown 반환
		auto it = objectMap.find(str);
		return (it != objectMap.end()) ? it->second : ObjectType::None;
	}
};