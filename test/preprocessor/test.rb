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

def pp_value(cpp_code)
  cpp_code.gsub(/^\s+/,'').gsub(/\s+$/,'').gsub(/\s+/,' ').strip
end

class TestPreprocessor < MiniTest::Test
  def test_hoge
    actual = pp_value <<-CPP
      #include <symbolset/preprocessor.hpp>
      HOGE
    CPP
    assert_equal actual, 'hoge'
  end
end
