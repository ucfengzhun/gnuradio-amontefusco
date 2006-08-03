/* -*- c++ -*- */
/*
 * Copyright 2006 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <qa_pmt_prims.h>
#include <cppunit/TestAssert.h>
#include <pmt.h>
#include <stdio.h>

void
qa_pmt_prims::test_symbols()
{
  CPPUNIT_ASSERT(!pmt_is_symbol(PMT_BOOL_T));
  CPPUNIT_ASSERT(!pmt_is_symbol(PMT_BOOL_F));
  CPPUNIT_ASSERT_THROW(pmt_symbol_to_string(PMT_BOOL_F), pmt_wrong_type);

  pmt_t sym1 = pmt_string_to_symbol("test");
  CPPUNIT_ASSERT(pmt_is_symbol(sym1));
  CPPUNIT_ASSERT_EQUAL(std::string("test"), pmt_symbol_to_string(sym1));
  CPPUNIT_ASSERT(pmt_is_true(sym1));
  CPPUNIT_ASSERT(!pmt_is_false(sym1));

  pmt_t sym2 = pmt_string_to_symbol("foo");
  pmt_t sym3 = pmt_string_to_symbol("test");
  CPPUNIT_ASSERT_EQUAL(sym1, sym3);
  CPPUNIT_ASSERT(sym1 != sym2);
  CPPUNIT_ASSERT(sym1 == sym3);

  static const int N = 2048;
  std::vector<pmt_t> v1(N);
  std::vector<pmt_t> v2(N);

  // generate a bunch of symbols
  for (int i = 0; i < N; i++){
    char buf[100];
    snprintf(buf, sizeof(buf), "test-%d", i);
    v1[i] = pmt_string_to_symbol(buf);
  }

  // confirm that they are all unique
  for (int i = 0; i < N; i++)
    for (int j = i + 1; j < N; j++)
      CPPUNIT_ASSERT(v1[i] != v1[j]);

  // generate the same symbols again
  for (int i = 0; i < N; i++){
    char buf[100];
    snprintf(buf, sizeof(buf), "test-%d", i);
    v2[i] = pmt_string_to_symbol(buf);
  }

  // confirm that we get the same ones back
  for (int i = 0; i < N; i++)
    CPPUNIT_ASSERT(v1[i] == v2[i]);
}

void
qa_pmt_prims::test_booleans()
{
  pmt_t sym = pmt_string_to_symbol("test");
  CPPUNIT_ASSERT(pmt_is_bool(PMT_BOOL_T));
  CPPUNIT_ASSERT(pmt_is_bool(PMT_BOOL_F));
  CPPUNIT_ASSERT(!pmt_is_bool(sym));
  CPPUNIT_ASSERT_EQUAL(pmt_from_bool(false), PMT_BOOL_F);
  CPPUNIT_ASSERT_EQUAL(pmt_from_bool(true), PMT_BOOL_T);
  CPPUNIT_ASSERT_EQUAL(false, pmt_to_bool(PMT_BOOL_F));
  CPPUNIT_ASSERT_EQUAL(true, pmt_to_bool(PMT_BOOL_T));
  CPPUNIT_ASSERT_THROW(pmt_to_bool(sym), pmt_wrong_type);
}

void
qa_pmt_prims::test_integers()
{
  pmt_t p1 = pmt_from_long(1);
  pmt_t m1 = pmt_from_long(-1);
  CPPUNIT_ASSERT(!pmt_is_integer(PMT_BOOL_T));
  CPPUNIT_ASSERT(pmt_is_integer(p1));
  CPPUNIT_ASSERT(pmt_is_integer(m1));
  CPPUNIT_ASSERT_THROW(pmt_to_long(PMT_BOOL_T), pmt_wrong_type);
  CPPUNIT_ASSERT_EQUAL(-1L, pmt_to_long(m1));
  CPPUNIT_ASSERT_EQUAL(1L, pmt_to_long(p1));
}

void
qa_pmt_prims::test_reals()
{
  pmt_t p1 = pmt_from_double(1);
  pmt_t m1 = pmt_from_double(-1);
  CPPUNIT_ASSERT(!pmt_is_real(PMT_BOOL_T));
  CPPUNIT_ASSERT(pmt_is_real(p1));
  CPPUNIT_ASSERT(pmt_is_real(m1));
  CPPUNIT_ASSERT_THROW(pmt_to_double(PMT_BOOL_T), pmt_wrong_type);
  CPPUNIT_ASSERT_EQUAL(-1.0, pmt_to_double(m1));
  CPPUNIT_ASSERT_EQUAL(1.0, pmt_to_double(p1));
  CPPUNIT_ASSERT_EQUAL(1.0, pmt_to_double(pmt_from_long(1)));
}

void
qa_pmt_prims::test_complexes()
{
  pmt_t p1 = pmt_make_rectangular(2, -3);
  pmt_t m1 = pmt_make_rectangular(-3, 2);
  CPPUNIT_ASSERT(!pmt_is_complex(PMT_BOOL_T));
  CPPUNIT_ASSERT(pmt_is_complex(p1));
  CPPUNIT_ASSERT(pmt_is_complex(m1));
  CPPUNIT_ASSERT_THROW(pmt_to_complex(PMT_BOOL_T), pmt_wrong_type);
  CPPUNIT_ASSERT_EQUAL(std::complex<double>(2, -3), pmt_to_complex(p1));
  CPPUNIT_ASSERT_EQUAL(std::complex<double>(-3, 2), pmt_to_complex(m1));
  CPPUNIT_ASSERT_EQUAL(std::complex<double>(1.0, 0), pmt_to_complex(pmt_from_long(1)));
  CPPUNIT_ASSERT_EQUAL(std::complex<double>(1.0, 0), pmt_to_complex(pmt_from_double(1.0)));
}

void
qa_pmt_prims::test_pairs()
{
  CPPUNIT_ASSERT(pmt_is_null(PMT_NIL));
  CPPUNIT_ASSERT(!pmt_is_pair(PMT_NIL));
  pmt_t s1 = pmt_string_to_symbol("s1");
  pmt_t s2 = pmt_string_to_symbol("s2");
  pmt_t s3 = pmt_string_to_symbol("s3");

  pmt_t c1 = pmt_cons(s1, PMT_NIL);
  CPPUNIT_ASSERT(pmt_is_pair(c1));
  CPPUNIT_ASSERT(!pmt_is_pair(s1));
  CPPUNIT_ASSERT_EQUAL(s1, pmt_car(c1));
  CPPUNIT_ASSERT_EQUAL(PMT_NIL, pmt_cdr(c1));

  pmt_t c3 = pmt_cons(s3, PMT_NIL);
  pmt_t c2 = pmt_cons(s2, c3);
  pmt_set_cdr(c1, c2);
  CPPUNIT_ASSERT_EQUAL(c2, pmt_cdr(c1));
  pmt_set_car(c1, s3);
  CPPUNIT_ASSERT_EQUAL(s3, pmt_car(c1));

  CPPUNIT_ASSERT_THROW(pmt_cdr(PMT_NIL), pmt_wrong_type);
  CPPUNIT_ASSERT_THROW(pmt_car(PMT_NIL), pmt_wrong_type);
  CPPUNIT_ASSERT_THROW(pmt_set_car(s1, PMT_NIL), pmt_wrong_type);
  CPPUNIT_ASSERT_THROW(pmt_set_cdr(s1, PMT_NIL), pmt_wrong_type);
}

void
qa_pmt_prims::test_vectors()
{
  static const size_t N = 3;
  pmt_t v1 = pmt_make_vector(N, PMT_NIL);
  CPPUNIT_ASSERT_EQUAL(N, pmt_length(v1));
  pmt_t s0 = pmt_string_to_symbol("s0");
  pmt_t s1 = pmt_string_to_symbol("s1");
  pmt_t s2 = pmt_string_to_symbol("s2");

  pmt_vector_set(v1, 0, s0);
  pmt_vector_set(v1, 1, s1);
  pmt_vector_set(v1, 2, s2);

  CPPUNIT_ASSERT_EQUAL(s0, pmt_vector_ref(v1, 0));
  CPPUNIT_ASSERT_EQUAL(s1, pmt_vector_ref(v1, 1));
  CPPUNIT_ASSERT_EQUAL(s2, pmt_vector_ref(v1, 2));

  CPPUNIT_ASSERT_THROW(pmt_vector_ref(v1, N), pmt_out_of_range);
  CPPUNIT_ASSERT_THROW(pmt_vector_set(v1, N, PMT_NIL), pmt_out_of_range);

  pmt_vector_fill(v1, s0);
  for (size_t i = 0; i < N; i++)
    CPPUNIT_ASSERT_EQUAL(s0, pmt_vector_ref(v1, i));
}

void
qa_pmt_prims::test_equivalence()
{
  pmt_t s0 = pmt_string_to_symbol("s0");
  pmt_t s1 = pmt_string_to_symbol("s1");
  pmt_t s2 = pmt_string_to_symbol("s2");
  pmt_t list0 = pmt_cons(s0, pmt_cons(s1, pmt_cons(s2, PMT_NIL)));
  pmt_t list1 = pmt_cons(s0, pmt_cons(s1, pmt_cons(s2, PMT_NIL)));
  pmt_t i0 = pmt_from_long(42);
  pmt_t i1 = pmt_from_long(42);
  pmt_t r0 = pmt_from_double(42);
  pmt_t r1 = pmt_from_double(42);
  pmt_t r2 = pmt_from_double(43);

  CPPUNIT_ASSERT(pmt_eq(s0, s0));
  CPPUNIT_ASSERT(!pmt_eq(s0, s1));
  CPPUNIT_ASSERT(pmt_eqv(s0, s0));
  CPPUNIT_ASSERT(!pmt_eqv(s0, s1));

  CPPUNIT_ASSERT(pmt_eqv(i0, i1));
  CPPUNIT_ASSERT(pmt_eqv(r0, r1));
  CPPUNIT_ASSERT(!pmt_eqv(r0, r2));
  CPPUNIT_ASSERT(!pmt_eqv(i0, r0));

  CPPUNIT_ASSERT(!pmt_eq(list0, list1));
  CPPUNIT_ASSERT(!pmt_eqv(list0, list1));
  CPPUNIT_ASSERT(pmt_equal(list0, list1));

  pmt_t v0 = pmt_make_vector(3, s0);
  pmt_t v1 = pmt_make_vector(3, s0);
  pmt_t v2 = pmt_make_vector(4, s0);
  CPPUNIT_ASSERT(!pmt_eqv(v0, v1));
  CPPUNIT_ASSERT(pmt_equal(v0, v1));
  CPPUNIT_ASSERT(!pmt_equal(v0, v2));

  pmt_vector_set(v0, 0, list0);
  pmt_vector_set(v0, 1, list0);
  pmt_vector_set(v1, 0, list1);
  pmt_vector_set(v1, 1, list1);
  CPPUNIT_ASSERT(pmt_equal(v0, v1));
}

void
qa_pmt_prims::test_misc()
{
  CPPUNIT_ASSERT_THROW(pmt_length(PMT_NIL), pmt_wrong_type);

  pmt_t k0 = pmt_string_to_symbol("k0");
  pmt_t k1 = pmt_string_to_symbol("k1");
  pmt_t k2 = pmt_string_to_symbol("k2");
  pmt_t k3 = pmt_string_to_symbol("k3");
  pmt_t v0 = pmt_string_to_symbol("v0");
  pmt_t v1 = pmt_string_to_symbol("v1");
  pmt_t v2 = pmt_string_to_symbol("v2");
  pmt_t p0 = pmt_cons(k0, v0);
  pmt_t p1 = pmt_cons(k1, v1);
  pmt_t p2 = pmt_cons(k2, v2);
  
  pmt_t alist = pmt_cons(p0, pmt_cons(p1, pmt_cons(p2, PMT_NIL)));
  CPPUNIT_ASSERT(pmt_eq(p1, pmt_assv(k1, alist)));
  CPPUNIT_ASSERT(pmt_eq(PMT_BOOL_F, pmt_assv(k3, alist)));
  
  pmt_t keys = pmt_cons(k0, pmt_cons(k1, pmt_cons(k2, PMT_NIL)));
  pmt_t vals = pmt_cons(v0, pmt_cons(v1, pmt_cons(v2, PMT_NIL)));
  CPPUNIT_ASSERT(pmt_equal(keys, pmt_map(pmt_car, alist)));
  CPPUNIT_ASSERT(pmt_equal(vals, pmt_map(pmt_cdr, alist)));
}

void
qa_pmt_prims::test_dict()
{
  pmt_t dict = pmt_make_dict();
  CPPUNIT_ASSERT(pmt_is_dict(dict));

  pmt_t k0 = pmt_string_to_symbol("k0");
  pmt_t k1 = pmt_string_to_symbol("k1");
  pmt_t k2 = pmt_string_to_symbol("k2");
  pmt_t k3 = pmt_string_to_symbol("k3");
  pmt_t v0 = pmt_string_to_symbol("v0");
  pmt_t v1 = pmt_string_to_symbol("v1");
  pmt_t v2 = pmt_string_to_symbol("v2");
  pmt_t v3 = pmt_string_to_symbol("v3");
  pmt_t not_found = pmt_cons(PMT_NIL, PMT_NIL);
  
  CPPUNIT_ASSERT(!pmt_dict_has_key(dict, k0));
  pmt_dict_set(dict, k0, v0);
  CPPUNIT_ASSERT(pmt_dict_has_key(dict, k0));
  CPPUNIT_ASSERT(pmt_eqv(pmt_dict_ref(dict, k0, not_found), v0));
  CPPUNIT_ASSERT(pmt_eqv(pmt_dict_ref(dict, k1, not_found), not_found));
  pmt_dict_set(dict, k1, v1);
  pmt_dict_set(dict, k2, v2);
  CPPUNIT_ASSERT(pmt_eqv(pmt_dict_ref(dict, k1, not_found), v1));
  pmt_dict_set(dict, k1, v3);
  CPPUNIT_ASSERT(pmt_eqv(pmt_dict_ref(dict, k1, not_found), v3));

  pmt_t keys = pmt_cons(k2, pmt_cons(k1, pmt_cons(k0, PMT_NIL)));
  pmt_t vals = pmt_cons(v2, pmt_cons(v3, pmt_cons(v0, PMT_NIL)));
  CPPUNIT_ASSERT(pmt_equal(keys, pmt_dict_keys(dict)));
  CPPUNIT_ASSERT(pmt_equal(vals, pmt_dict_values(dict)));
}