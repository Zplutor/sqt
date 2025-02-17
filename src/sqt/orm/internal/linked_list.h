#pragma once

namespace sqt {

template<typename NODE_BASE>
class LinkedList {
public:
    class Node : public NODE_BASE {
    public:
        constexpr explicit Node(const Node*& last) noexcept : previous_(last) {
            if (last) {
                index_ = last->index_ + 1;
            }
            last = this;
        }

        constexpr const Node* GetPrevious() const noexcept {
            return previous_;
        }

        constexpr std::size_t GetIndex() const noexcept {
            return index_;
        }

    private:
        const Node* previous_{};
        std::size_t index_{};
    };
    
public:
    constexpr LinkedList() noexcept = default;

    constexpr const Node* Last() const noexcept {
        return last_;
    }

    constexpr const Node*& Last() noexcept {
        return last_;
    }

    constexpr std::size_t Count() const noexcept {
        std::size_t result{};
        auto current = last_;
        while (current) {
            ++result;
            current = current->GetPrevious();
        }
        return result;
    }

    template<std::size_t SIZE>
    constexpr auto ToNodeBaseArray() const noexcept {
        std::array<const NODE_BASE*, SIZE> result; 
        FillNodeBaseArray<SIZE>(result, 0, last_);
        return result; 
    }

private:
    template<std::size_t SIZE>
    static constexpr void FillNodeBaseArray(
        std::array<const NODE_BASE*, SIZE>& array,
        std::size_t index,
        const NODE_BASE* node_base) {

        if (index >= array.size()) {
            return;
        }
        array[SIZE - index - 1] = node_base;
        FillNodeBaseArray<SIZE>(
            array, 
            ++index, 
            static_cast<const Node*>(node_base)->GetPrevious());
    }

private:
    const Node* last_{};
};

}