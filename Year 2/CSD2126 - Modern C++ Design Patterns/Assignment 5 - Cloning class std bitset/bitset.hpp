/*!************************************************************************
  \file bitset.hpp

  \author Bryan Ang Wei Ze

  \par DP email: bryanweize.ang\@digipen.edu

  \par Course: CSD2126 Modern C++ Design Patterns

  \par Programming Assignment #5

  \date 31-10-2024
  
  \brief
  This file contains member functions definitions of class template bitset
**************************************************************************/

namespace HLP3
{
    template <size_t N>
    bitset<N>::bitset()
        : data(new bool[N]{})
    {

    }

    template <size_t N>
    bitset<N>::bitset(const bitset& rhs)
        : data(new bool[N]{})
    {
        for (size_t i = 0; i < N; ++i)
        {
            data[i] = rhs.data[i];
        }
    }

    template <size_t N>
    bitset<N>& bitset<N>::operator=(const bitset& rhs)
    {
        bitset tmp{rhs};
        std::swap(tmp, *this);
        return *this;
    }

    template <size_t N>
    bitset<N>::bitset(bitset&& rhs) noexcept
        : data(rhs.data)
    {
        rhs.data = nullptr;
    }

    template <size_t N>
    bitset<N>& bitset<N>::operator=(bitset&& rhs) noexcept
    {
        data = rhs.data;
        rhs.data = nullptr;
        return *this;
    }

    template <size_t N>
    bitset<N>::~bitset()
    {
        delete[] data;
    }

    template <size_t N>
    void bitset<N>::set(size_t pos, bool val)
    {
        if (pos >= N)
        {
            throw std::out_of_range("Index out of range");
        }

        data[N - 1 - pos] = val;
    }

    template <size_t N>
    void bitset<N>::reset(size_t pos)
    {
        if (pos >= N)
        {
            throw std::out_of_range("Index out of range");
        }

        data[N - 1 - pos] = false;
    }

    template <size_t N>
    void bitset<N>::flip(size_t pos)
    {
        if (pos >= N)
        {
            throw std::out_of_range("Index out of range");
        }
        
        data[N - 1 - pos] = !data[N - 1 - pos];
    }

    template <size_t N>
    std::string bitset<N>::to_string(char zero, char one) const
    {
        std::string result;
        for (size_t i = 0; i < N; ++i)
        {
            if (data[i])
            {
                result += one;
            }
            else
            {
                result += zero;
            }
        }
        return result;
    }

    template <size_t N>
    bool bitset<N>::test(size_t pos) const
    {
        if (pos >= N)
        {
            throw std::out_of_range("Index out of range");
        }
        
        return data[N - 1 - pos];
    }

    template <size_t N>
    constexpr size_t bitset<N>::size() noexcept 
    {
        return N;
    }

    template <size_t N>
    bool bitset<N>::operator[](size_t pos) const
    {
        return data[pos];
    }

    template <size_t N>
    size_t bitset<N>::count() const noexcept
    {
        size_t count_bits = 0;
        for (size_t i = 0; i < N; ++i)
        {
            if (data[i])
            {
                ++count_bits;
            }
        }
        return count_bits;
    }
}