require 'net/http'
require 'cgi'

class InputHelper

  def get_input(puzzle_day = 1, year = 2024, force_refresh = false)
    dir_name = "./inputs/#{year}" 
    Dir.mkdir(dir_name) unless Dir.exist?(dir_name)

    file_name = "#{dir_name}/day_#{puzzle_day}.txt"    
    if !force_refresh and File.exist?(file_name)
      puts "Loading input from file"

      return File.read(file_name)
    end
    
    input = fetch_input(puzzle_day, year)
    File.open(file_name, "w+") { |file| file.write(input) }   
    return input    
  end
  
  private
  
  def read_token()
    begin
      token_file = File.open("token.txt", "r")
      token_data = token_file.read
      raise RuntimeError, "Something wrong with token.txt" unless token_data and token_data.length > 0
      puts "Access token :: ...#{token_data[10..30]}..."
      
      return token_data
    ensure
      token_file.close
    end
  end
  
  def fetch_input(day, year)
    access_token = read_token()
    uri = URI("https://adventofcode.com/#{year}/day/#{day}/input")
    puts "Fetching input... #{uri}"

    begin
      request_object = Net::HTTP::Get.new(uri, {
        'User-Agent' => 'https://github.com/carloshrm/',
      })

      cookie_object = CGI::Cookie.new('session', access_token)
      request_object['Cookie'] = cookie_object.to_s   
      
      response = Net::HTTP.start(uri.hostname, :use_ssl => true) do |http|
        http.request(request_object)
      end

      puts "Input fetched :: #{response.body[5..20]}"
      return response.body
    end
  end
end
