# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information
from exhale import utils
import os

project = 'LightningScanner'
copyright = '2023, localcc'
author = 'localcc'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [ "sphinx.ext.autosummary", "exhale", "breathe" ]

doxygen_output_dir = os.getenv("DOXYGEN_OUTPUT_DIR")

breathe_projects = {
	"LightningScanner": f"{doxygen_output_dir}/xml"
}
breathe_default_project = "LightningScanner"

def specificationsForKind(kind):
	if kind == "class" or kind == "struct":
		return [
			":members:",
			":undoc-members:",
			":private-members:"
		]
	else:
		return []

exhale_args = {
	"containmentFolder": "./api",
	"rootFileName": "library_root.rst",
	"doxygenStripFromPath": ".",
	"rootFileTitle": "C++ API Reference",
	"kindsWithContentsDirectives": [],
	"createTreeView": True,
	"customSpecificationsMapping": utils.makeCustomSpecificationsMapping(specificationsForKind),
	"exhaleExecutesDoxygen": True,
	"exhaleDoxygenStdin": """PROJECT_NAME=LightningScanner
	INPUT=../include
	RECURSIVE=YES
	GENERATE_XML=YES"""
}

primary_domain = 'cpp'
highlight_language = 'cpp'

master_doc = "index"
templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']



# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'furo'
html_static_path = ['_static']
