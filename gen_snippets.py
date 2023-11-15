import os
import json
from typing import TypedDict

prefix: str = "vasito_"

code_dirs: list[str] = [
  "data_structures",
  "flow",
  "geometry",
  "graphs",
  "math",
  "other",
  "strings"
]

class SingleSnippet(TypedDict):
  prefix: str
  body: list[str]

Snippets = dict[str, SingleSnippet]


def get_snippet(file_path: str) -> Snippets:
  with open(file_path, 'r') as f:
    code: str = f.read()
  file_name: str = os.path.basename(file_path)
  name: str = os.path.splitext(file_name)[0]
  this_prefix: str = prefix + name
  code = code.replace("#pragma once", "")
  code = code.replace("#include <IncludeTemplate.hpp>", "")
  code = code.strip()
  return {
    file_name: {
      'prefix': this_prefix,
      'body': code.split('\n'),
    }
  }

def create_snippet_file(snippets: Snippets, file_path: str):
  with open(file_path, 'w') as f:
    json.dump(snippets, f, indent=2)

def combine_snippets(file_paths: list[str]) -> Snippets:
  snippets: Snippets = {}
  for file_path in file_paths:
    with open(file_path, 'r') as f:
      file_snippets = json.load(f)
    snippets.update(file_snippets)
  return snippets

def main():
  this_dir: str = os.path.dirname(__file__)
  output_dir: str = os.path.join(os.path.dirname(__file__), 'snippets')
  cpp_snippets_dir: str = os.path.join(output_dir, 'cpp')

  if not os.path.exists(output_dir):
    os.makedirs(output_dir)
  if not os.path.exists(cpp_snippets_dir):
    os.makedirs(cpp_snippets_dir)

  snippets_file_paths: list[str] = []

  for dir in code_dirs:
    code_dir: str = os.path.join(this_dir, dir)
    for root, _, files in os.walk(code_dir):
      if os.path.basename(root) == 'templates':
        continue
      for file in files:
        file_path: str = os.path.join(root, file)
        name, ext = os.path.splitext(file_path)
        name = os.path.basename(name)
        if ext not in ['.hpp', '.cpp'] or 'template' in name or 'test' in name:
          continue

        print(f"Generating snippet for {name}")

        snippet: Snippets = get_snippet(file_path)
        output_file: str = os.path.join(cpp_snippets_dir, name + '.json')
        create_snippet_file(snippet, output_file)
        snippets_file_paths.append(output_file)

  print("Combining all snippets")
  
  snippets: Snippets = combine_snippets(snippets_file_paths)
  full_output_file: str = os.path.join(output_dir, 'cpp.json')
  create_snippet_file(snippets, full_output_file)

if __name__ == '__main__':
  main()
