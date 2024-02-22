#include <iostream>
#include <unordered_map>
#include <memory>

class AActor
{
public:
    uint32_t ID = 0;

    AActor() noexcept
        : ID{0}
    {
    }

    explicit AActor(uint32_t InID) noexcept
        : ID{InID}
    {
    }

    virtual ~AActor() noexcept {}
    virtual void OnCreate() {}
    virtual void OnUpdate(float Delta) {}
    virtual void OnDestroy() {}
};

class CComponent
{
public:
};

class FWorld
{
public:
    std::shared_ptr<AActor> GetByID(uint32_t InID)
    {

    }
    
    //std::shared_ptr<AActor> Create

private:
    std::unordered_map<uint32_t, size_t> mIDLookUp;
    std::vector<std::shared_ptr<AActor>> mActors{};
    uint32_t mLastID = 0;
};

int main(int argc, char** argv)
{

}