#include "data_dictionary_file.h"

namespace dictionary {

	
	DataDictionaryFile::DataDictionaryFile(){ 
		
		id_ = 0;
		std::string path = "/home/ghostdev/Projects/cc/file_structures/";
		std::string tmp_dir = "tmp/";
		std::string tmp_name = "unamed";
		std::string ext = ".dat";
       
		path_ = path;
		dir_ = tmp_dir;
		name_ = tmp_name; 
		ext_ = ext;
        
        file_header_ = -1;
		
         
	}

	DataDictionaryFile::DataDictionaryFile(const std::string& name){ 
		
		id_ = 0;
		std::string path = "/home/ghostdev/Projects/cc/file_structures/";
		std::string tmp_dir = "tmp/";
		std::string ext = ".dat";

		path_ = path;
		dir_ = tmp_dir;
		name_ = name; 
		ext_ = ext;
        
        file_header_ = -1;
	}



	DataDictionaryFile::~DataDictionaryFile(){}
	
	void DataDictionaryFile::SetId(int id){ id_ = id; }
	void DataDictionaryFile::SetName(const std::string& name){ name_ = name; }
	void DataDictionaryFile::SetDir(const std::string& dir){ dir_ = dir; }
	void DataDictionaryFile::SetPath(const std::string& path){ path_ = path; }
	void DataDictionaryFile::SetExt(const std::string& ext){ ext_ = ext; }
    void DataDictionaryFile::SetFileHeader(long int file_header){ file_header_ = file_header; }

    int DataDictionaryFile::GetId(){ return id_;}
    std::string DataDictionaryFile::GetName(){ return name_;}
    std::string DataDictionaryFile::GetDir(){ return dir_;}
    std::string DataDictionaryFile::GetPath(){ return path_;}
    std::string DataDictionaryFile::GetExt(){ return ext_;}
    long int DataDictionaryFile::GetFileHeader(){return file_header_;}
    
    long int DataDictionaryFile::GetFileSize(){
    	std::streampos file_begin, file_end;
		std::ifstream file ( name_ + ext_, std::ifstream::binary );
		file_begin = file.tellg();
		file.seekg (0, std::ifstream::end);
		file_end = file.tellg();
		file.close();
		file_size_ = file_end - file_begin;
		return file_size_;
    }
    
   void DataDictionaryFile::CreateFile(){
   		    std::ofstream file ( name_ + ext_, std::ofstream::binary | std::ofstream::out );
			file.seekp (0);
			file.write( (char*) &file_header_, sizeof(long int) );
			file.close();
	        std::cout << std::endl << name_ + ext_ << " successfully created file!" << std::endl;
   }

    void DataDictionaryFile::AddEntity(Entity entity){
    	char name[MAX_LENGTH_NAME_ENTTITY_];
    	for (int i = 0; i < MAX_LENGTH_NAME_ENTTITY_; i++){
            name[i] = entity.GetName()[i];      
        }
        long int entity_address = entity.GetEntityAddress();
    	long int attribute_address = entity.GetAttributeAddress();
    	long int data_address = entity.GetDataAddress();
    	long int next_entity_address = entity.GetNextEntityAddress();

		std::cout << "::>>>> " << entity_address << std::endl;
		std::cout << "::>>>> " << attribute_address << std::endl;
		std::cout << "::>>>> " << data_address << std::endl;
		std::cout << "::>>>> " << next_entity_address << std::endl;

        
    	list_entities_.push_back(entity);
		
		std::fstream file ( name_ + ext_, std::fstream::binary | std::fstream::out );
        
    	file.seekg(0, std::fstream::end);
		int file_length = file.tellg(); // Entity Address

		
		std::cout << std::endl << ":::::: File Size ::::::: ===>  " << file_length << std::endl;
		std::cout << std::endl << ":::::: Header ::::::: ===>  " << file_header_ << std::endl;

		file.seekg( file_length + sizeof(dictionary::Entity), std::fstream::end  );
		
		file.seekp (0);
		file.write( (char*) &file_header_, sizeof(long int) );
		
		file.close();
		std::fstream efile ( name_ + ext_, std::fstream::binary | std::fstream::out );
		efile.seekg (file_size_, std::fstream::end);

		efile.write( (char*) &name, MAX_LENGTH_NAME_ENTTITY_ );
		efile.write( (char*) &entity_address, sizeof(long int) );
		efile.write( (char*) &attribute_address, sizeof(long int) );
		efile.write( (char*) &data_address, sizeof(long int) );
		efile.write( (char*) &next_entity_address, sizeof(long int) );
	    
	    std::cout << std::endl << name_ + ext_ << " successfully updated file!"  << std::endl;
		efile.close(); 

    }

    void DataDictionaryFile::AddAttribute(Attribute attribute){
    	list_attributes_.push_back(attribute);
    	//std::streampos begin_position, end_position;
    	std::fstream file ( name_ + ext_, std::fstream::binary | std::fstream::out );
        //begin_position = file.tellg();
		file.seekg (file_size_, std::fstream::end);
		file.write( (char*) &attribute, sizeof(dictionary::Attribute) );
		//end_position = file.tellg();
        //file.write( (char*) &file_header_, sizeof(long int) );
        std::cout << std::endl << name_ + ext_ << " successfully updated file!"  << std::endl;
		file.close(); 
    }

    

}  // end namespace dictionary
