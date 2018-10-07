Pod::Spec.new do |s|
	s.name                = "RUN"
	s.module_name         = "RUN"
	s.version             = "0.1.0"
	s.summary             = "Small multi-platform game engine"
	s.homepage            = "https://github.com/TenteiCo/RUN"
	s.license             = {:type => 'MIT', :file => 'copying.txt'}
	s.authors             = "Tentei"
	s.source              = {:git => "https://github.com/TenteiCo/RUN.git", :tag => s.version.to_s}
	s.requires_arc        = false
	s.header_dir          = "glm"
	s.header_mappings_dir = "glm"
	s.libraries           = 'c++'
	s.source_files        = 'glm/**/*{.h,.hpp}'
	s.xcconfig            = {'LIBRARY_SEARCH_PATHS' => '$(PODS_ROOT)/glm'}
	s.preserve_paths      = 'glm/**/*{.h,.hpp,.inl}'
	s.public_header_files = 'API/C++/RUN/**/*.h' 
end
