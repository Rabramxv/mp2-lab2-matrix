#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)  
{                                                            
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)    
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length) 
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
    int arr[] = { 1, 2, 3, 4, 5 }; 
    TDynamicVector<int> original(arr, 5);
    TDynamicVector<int> copied = original; 
    EXPECT_EQ(original, copied);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    TDynamicVector<int> original(arr, 5);
    TDynamicVector<int> copied = original;
    copied[0] = 10; 
    EXPECT_NE(original[0], copied[0]); 
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

//TEST(TDynamicVector, can_set_and_get_element)
//{
//  TDynamicVector<int> v(4);
//  v[0] = 4;
//
//  EXPECT_EQ(4, v[0]);
//}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
    TDynamicVector<int> v(5);
    ASSERT_ANY_THROW(v.at(-1)); 
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    TDynamicVector<int> v(5); 
    ASSERT_ANY_THROW(v.at(5)); 
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
    TDynamicVector<int> v(5);
    ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size) 
{
    TDynamicVector<int> v1(5);
    TDynamicVector<int> v2(5);
    ASSERT_NO_THROW(v1 = v2); 
    ASSERT_EQ(v1.size(), v2.size()); 
}

TEST(TDynamicVector, assign_operator_change_vector_size) 
{
    TDynamicVector<int> v1(5);
    TDynamicVector<int> v2(10);
    v1 = v2;
    EXPECT_EQ(v1.size(), 10); 
}

TEST(TDynamicVector, can_assign_vectors_of_different_size) 
{
    TDynamicVector<int> v1(5);
    TDynamicVector<int> v2(10);
    for (size_t i = 0; i < 5; ++i) {
        v1[i] = i + 1; // {1, 2, 3, 4, 5}
    }
    for (size_t i = 0; i < 10; ++i) {
        v2[i] = (i + 1) * 2; // {2, 4, 6, 8, 10, 12, 14, 16, 18, 20}
    }

    v1 = v2;

    EXPECT_EQ(v1.size(), 10); 
    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(v1[i], (i + 1) * 2); 
    }
}

TEST(TDynamicVector, compare_equal_vectors_return_true) 
{
    TDynamicVector<int> v1(5);
    TDynamicVector<int> v2(5);
    for (size_t i = 0; i < 5; ++i) {
        v1[i] = i + 1; // {1, 2, 3, 4, 5}
        v2[i] = i + 1; // {1, 2, 3, 4, 5}
    }
    EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    TDynamicVector<int> v(5);
    for (size_t i = 0; i < 5; ++i) {
        v[i] = i + 1; // {1, 2, 3, 4, 5}
    }
    EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    TDynamicVector<int> v1(5);
    TDynamicVector<int> v2(10);
    for (size_t i = 0; i < 5; ++i) {
        v1[i] = i + 1; // {1, 2, 3, 4, 5}
    }
    for (size_t i = 0; i < 10; ++i) {
        v2[i] = (i + 1) * 2; // {2, 4, 6, 8, 10, ...}
    }
    EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
    TDynamicVector<int> v(5);
    for (size_t i = 0; i < 5; ++i) {
        v[i] = i + 1; // {1, 2, 3, 4, 5}
    }
    TDynamicVector<int> result = v + 10; 
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(result[i], (i + 1) + 10); // Îæèäàåì {11, 12, 13, 14, 15}
    }
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
    TDynamicVector<int> v(5);
    for (size_t i = 0; i < 5; ++i) {
        v[i] = i + 5; // {5, 6, 7, 8, 9}
    }
    TDynamicVector<int> result = v - 3; // {2, 3, 4, 5, 6}
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(result[i], (i + 5) - 3);
    }
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    TDynamicVector<int> v(4);
    for (size_t i = 0; i < 4; ++i) {
        v[i] = i + 1; // {1, 2, 3, 4}
    }
    TDynamicVector<int> result = v * 2; // {2, 4, 6, 8}
    for (size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(result[i], (i + 1) * 2);
    }
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
    TDynamicVector<int> v1(3);
    TDynamicVector<int> v2(3);
    for (size_t i = 0; i < 3; ++i) {
        v1[i] = i + 1; //  {1, 2, 3}
        v2[i] = i + 4; //  {4, 5, 6}
    }
    TDynamicVector<int> result = v1 + v2; // {5, 7, 9}
    for (size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(result[i], (i + 1) + (i + 4));
    }
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(3);
    TDynamicVector<int> v2(4);
    for (size_t i = 0; i < 3; ++i) {
        v1[i] = i + 1; // {1, 2, 3}
    }
    for (size_t i = 0; i < 4; ++i) {
        v2[i] = (i + 1) * 2; // {2, 4, 6, 8}
    }
    
    EXPECT_THROW(v1 + v2, std::invalid_argument);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
    TDynamicVector<int> v1(3);
    TDynamicVector<int> v2(3);
    for (size_t i = 0; i < 3; ++i) {
        v1[i] = i + 5; // {5, 6, 7}
        v2[i] = i + 2; // {2, 3, 4}
    }
    TDynamicVector<int> result = v1 - v2; // {3, 3, 3}
    for (size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(result[i], v1[i] - v2[i]);
    }
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(3);
    TDynamicVector<int> v2(4);
    for (size_t i = 0; i < 3; ++i) {
        v1[i] = i + 1; // {1, 2, 3}
    }
    for (size_t i = 0; i < 4; ++i) {
        v2[i] = (i + 1) * 2; // {2, 4, 6, 8}
    }
    
    EXPECT_THROW(v1 - v2, std::invalid_argument);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
    TDynamicVector<int> v1(3);
    TDynamicVector<int> v2(3);
    for (size_t i = 0; i < 3; ++i) {
        v1[i] = i + 1;  // {1, 2, 3}
        v2[i] = i + 4;  // {4, 5, 6}
    }
   
    int result = v1 * v2; // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
    EXPECT_EQ(result, 32);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(3);
    TDynamicVector<int> v2(4);
    for (size_t i = 0; i < 3; ++i) {
        v1[i] = i + 1; // {1, 2, 3}
    }
    for (size_t i = 0; i < 4; ++i) {
        v2[i] = (i + 1) * 2; // {2, 4, 6, 8}
    }
    EXPECT_THROW(v1 * v2, std::invalid_argument);
}
