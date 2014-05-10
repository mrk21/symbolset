if ARGV.size == 3 then
  CXX = ARGV[0]
  CXXFLAGS = ARGV[1].gsub('\\','')
  INCS = ARGV[2].split(/\s+/).map{|v| "-I#{v}"}.join(' ')
  
  cpp_cmd = [CXX, CXXFLAGS, INCS, __FILE__].join(' ')
  ruby_cmd = 'ruby - -v'
  puts [cpp_cmd, ruby_cmd].join(' | ')
  
  IO.popen(cpp_cmd,'r') do |cpp|
    IO.popen(ruby_cmd,'w') do |ruby|
      ruby.write cpp.read
    end
  end
  exit
end

require 'minitest'
require 'minitest/autorun'

module Symbolset 
  module Processor
    class TestBase < MiniTest::Test
      CPP_CODE =<<-CPP
        #include <symbolset/preprocessor.hpp>
      CPP
      
      def cxxpp(cpp_code)
        cpp_code.gsub(/^\s+/,'').gsub(/\s+$/,'').gsub(/\s+/,' ').strip
      end
   end
    
    #// SYMBOLSET_PP_ARG_TUPLE(data_tuple)
    class Test_SYMBOLSET_PP_ARG_TUPLE < TestBase
      def test_get
        assert_equal cxxpp(<<-CPP), '(1,2)'
          SYMBOLSET_PP_ARG_TUPLE(((1,2),(a,b,c)))
        CPP
      end
    end
    
    #// SYMBOLSET_PP_VAL_TUPLE(data_tuple)
    class Test_SYMBOLSET_PP_VAL_TUPLE < TestBase
      def test_get
        assert_equal cxxpp(<<-CPP), '(a,b,c)'
          SYMBOLSET_PP_VAL_TUPLE(((1,2),(a,b,c)))
        CPP
      end
    end
    
    #// SYMBOLSET_PP_ARG(i, data_tuple)
    class Test_SYMBOLSET_PP_ARG < TestBase
      def test_get
        assert_equal cxxpp(<<-CPP), '2'
          SYMBOLSET_PP_ARG(1,((1,2),(a,b,c)))
        CPP
      end
    end
    
    #// SYMBOLSET_PP_VAL(i, data_tuple)
    class Test_SYMBOLSET_PP_VAL < TestBase
      def test_get
        assert_equal cxxpp(<<-CPP), 'b'
          SYMBOLSET_PP_VAL(1,((1,2),(a,b,c)))
        CPP
      end
    end
    
    #// SYMBOLSET_PP_STR(i, data_tuple)
    class Test_SYMBOLSET_PP_STR < TestBase
      def test_get
        assert_equal cxxpp(<<-CPP), '"b"'
          SYMBOLSET_PP_STR(1,((1,2),(a,b,c)))
        CPP
      end
    end
    
    #// SYMBOLSET_PP_EACH(callback, data_tuple)
    class Test_SYMBOLSET_PP_EACH < TestBase
      def test_iterate
        assert_equal cxxpp(<<-CPP), 'int type::a; int type::b; int type::c;'
          #define callback(x,i,v) int BOOST_PP_TUPLE_ELEM(0,BOOST_PP_TUPLE_ELEM(0,v))::BOOST_PP_TUPLE_ELEM(i,BOOST_PP_TUPLE_ELEM(1,v));
          SYMBOLSET_PP_EACH(callback, ((type),(a,b,c)))
          #undef callback
        CPP
      end
    end
    
    #// SYMBOLSET_PP_SYMBOL_LIST(data_tuple)
    class Test_SYMBOLSET_PP_SYMBOL_LIST < TestBase
      def test_output
        expected = [
          'static constexpr value_type a = static_cast<value_type>(0);',
          'static constexpr value_type b = static_cast<value_type>(1);',
          'static constexpr value_type c = static_cast<value_type>(2);',
        ]
        assert_equal cxxpp(<<-CPP), expected.join(' ')
          SYMBOLSET_PP_SYMBOL_LIST(((type),(a,b,c)))
        CPP
      end
    end
    
    #// SYMBOLSET_PP_NAME_LIST(data_tuple)
    class Test_SYMBOLSET_PP_NAME_LIST < TestBase
      def test_output
        expected = [
          '{::symbolset::val(type::a), "a"}',
          '{::symbolset::val(type::b), "b"}',
          '{::symbolset::val(type::c), "c"}',
        ]
        assert_equal cxxpp(<<-CPP), expected.join(', ')
          SYMBOLSET_PP_NAME_LIST(((type),(a,b,c)))
        CPP
      end
    end
    
    #// SYMBOLSET_PP_ASSERT_LIST(data_tuple)
    class Test_SYMBOLSET_PP_ASSERT_LIST < TestBase
      def test_output
        expected = [
          %{static_assert("a"[0] != '\u0000', "Symbol name is empty! (index: " "0" ")");},
          %{static_assert("b"[0] != '\u0000', "Symbol name is empty! (index: " "1" ")");},
          %{static_assert("c"[0] != '\u0000', "Symbol name is empty! (index: " "2" ")");},
        ]
        assert_equal cxxpp(<<-CPP), expected.join(' ')
          SYMBOLSET_PP_ASSERT_LIST(((type),(a,b,c)))
        CPP
      end
    end
  end
end
