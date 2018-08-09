#! /usr/bin/env python3

# Copyright 2018, Niels Ole Salscheider
#
# This file is part of Babilas.
#
# Babilas is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Babilas is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Babilas. If not, see <https://www.gnu.org/licenses/>.

import io
import sys
import argparse
import xml.etree.ElementTree as ET
import re

arg_parser = argparse.ArgumentParser(description='Convert the unicode emoji '
    'list to an XML file for the emoji picker. You can download the list here: '
    'https://unicode.org/Public/emoji/11.0/emoji-test.txt')
arg_parser.add_argument('input', help='Path to the input txt file')
arg_parser.add_argument('output', help='Path to the output XML file')
argv = sys.argv
del argv[0]
args = arg_parser.parse_args(argv)

skin_tones = [ 0x1F3FB, 0x1F3FC, 0x1F3FD, 0x1F3FE, 0x1F3FF ]

collectionElem = ET.Element('collection')
with io.open (args.input, 'r', encoding='utf-8') as input_file:
    for line in input_file:
        if line.startswith('# group: '):
            categoryElem = ET.SubElement(collectionElem, 'category')
            categoryNameElem = ET.SubElement(categoryElem, 'name')
            categoryNameElem.text = line.replace('# group: ', '')
            groupElem = ET.SubElement(categoryElem, 'emojis')
        elif re.match('^[0-9a-fA-F]{4}', line):
            if 'non-fully-qualified' in line:
                continue
            assert 'fully-qualified' in line
            match = re.search('^(?:([0-9a-fA-F]{4,}) )+', line)
            emoji = ''
            do_not_add = False
            for entry in match.group(0).split(' '):
                if entry:
                    if int(entry, 16) in skin_tones:
                        do_not_add = True
                    emoji += chr(int(entry, 16))
            assert emoji
            if do_not_add:
                continue

            match = re.search('# ' + emoji + ' (.*)$', line)
            if not match:
                print('Warning: No match for ' + emoji)
                continue
            description = match.group(1)
            #if '🥰' in description:
            #    # This emoji was recently added. We skip it for now.
            #    continue

            emojiElem = ET.SubElement(groupElem, 'emoji')
            characterElem = ET.SubElement(emojiElem, 'character')
            characterElem.text = emoji
            descElem = ET.SubElement(emojiElem, 'desc')
            descElem.text = description

ET.ElementTree(collectionElem).write(args.output, encoding='utf-8')

