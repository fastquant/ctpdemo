#!/usr/bin/env ruby

require 'nokogiri'

file = ARGV[0]

File.open(file) do |f|
  doc = Nokogiri::XML(f)
  root = doc.root
  pkgs = root.xpath("packages/packageDefine")
  tids = root.xpath("tids/tidDefine")
  fields = root.xpath("fields/fieldDefine")
  items = root.xpath("items/itemDefine")
  types = root.xpath("types/typeDefine")
  puts pkgs.count
  puts tids.count
  puts fields.count
  puts items.count
  puts types.count
end
