#include <iostream>
#include <vector>
#include <memory>

/*
What it is:


Useful for:
 - Turn-based games where you can cancel your move that you made.
 - Undo/redo system for editors.
 - Maybe in rollback netcode fighting games.

Example games/programs:
 - Hearthstone
 - Into the Breach
*/

class AActor
{
public:
    explicit AActor(uint32_t ID) noexcept
        : m_ID(ID)
    {
    }
    void Jump() const
    {
        std::cout << "Actor #" << m_ID << " jumps!\n";
    }

    void Shoot(int32_t Amount) const
    {
        std::cout << "Actor #" << m_ID << " shoots " << Amount << " times!\n";
    }

private:
    uint32_t m_ID = 0;
};

class FCommand
{
public:
    virtual ~FCommand() {  }
    virtual void Execute(AActor& Actor) const = 0;
};

class FShootCommand final : public FCommand
{
public:
    explicit FShootCommand(int32_t Amount) noexcept
        : m_Amount(Amount)
    {
    }

    void Execute(AActor& Actor) const
    {
        Actor.Shoot(m_Amount);
    }

private:
    int32_t m_Amount = 0;
};

class FJumpCommand final : public FCommand
{
public:
    void Execute(AActor& Actor) const
    {
        Actor.Jump();
    }
};

int main(int argc, char** argv)
{
    // Create our DS
    std::vector<std::unique_ptr<FCommand>> CommandList;

    // Record actions of player
    AActor Player(1);
    CommandList.emplace_back(std::move(std::make_unique<FJumpCommand>()));
    CommandList.emplace_back(std::move(std::make_unique<FShootCommand>(15)));
    CommandList.emplace_back(std::move(std::make_unique<FJumpCommand>()));
    CommandList.emplace_back(std::move(std::make_unique<FShootCommand>(3)));
    CommandList.emplace_back(std::move(std::make_unique<FJumpCommand>()));

    // Execute the actions of player
    for (const auto& Command : CommandList)
    {
        Command->Execute(Player);
    }

    // We could go backwards with a reverse iterator and could call Undo(Player) to undo

    // Empty our DS
    CommandList.clear();

    std::cin.get();
}