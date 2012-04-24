/*
 * @author Mário Soares
 * @contributors Jefferson González
 * 
 * @license 
 * This file is part of wxPHP check the LICENSE file for information.
 * 
 * @description
 * Main start point for the wxWidgets php extension
 * 
 * @note
 * Some parts of this file are auto-generated by the wxPHP source maker
*/

#include "php_wxwidgets.h"
#include "app.h"

/**
 * Custom function to register global objects as constants
 */
BEGIN_EXTERN_C()
ZEND_API void wxphp_register_resource_constant(const char *name, uint name_len, void* resource, zend_class_entry* class_entry, int list_entry, int flags, int module_number TSRMLS_DC)
{
	zend_constant c;
	char _wxResource[] = "wxResource";
	
	object_init_ex(&c.value, class_entry);
	add_property_resource(&c.value, _wxResource, zend_list_insert(resource, list_entry));
	
	c.value.type = IS_OBJECT;
	c.flags = flags;
	c.name = zend_strndup(name, name_len-1);
	c.name_len = name_len;
	c.module_number = module_number;
	zend_register_constant(&c TSRMLS_CC);
}
END_EXTERN_C()

/**
 * Space reserved for the zend_class_entry declaration of each class
 */
<?php print $entries ?>

/**
 * Predefined handcoded class entry for wxApp
 */
char PHP_wxApp_NAME[] = "wxApp";
char le_wxApp_name[] = "native wxApp";
zend_class_entry *php_wxApp_entry;
int le_wxApp;

/**
 * Predefined handcoded set of functions
 */
PHP_FUNCTION(php_wxInitialize)
{
	wxInitAllImageHandlers();
	RETVAL_BOOL(wxInitialize());
}

PHP_FUNCTION(php_wxInitAllImageHandlers)
{
	wxInitAllImageHandlers();
	RETVAL_TRUE;
}

PHP_FUNCTION(php_wxExecute)
{
	char* _argStr0;
	int _argStr0_len;
	
	char parse_parameters[] = "s";
    
	if (zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, parse_parameters, &_argStr0 , &_argStr0_len ) == SUCCESS)
	{
		long ret0;
		ret0 = wxExecute(wxString(_argStr0, wxConvUTF8));
		
		RETURN_LONG((long)ret0)
	}
}

PHP_FUNCTION(php_wxEntry)
{
	int argc = 1;
	char application_name[] = "wxPHP";
	char *argv[2] = { application_name, NULL };
	
	RETVAL_LONG(wxEntry(argc,argv));
}

PHP_FUNCTION(php_wxAboutBox)
{
    zval **tmp;
	int id_to_find;
	wxAboutDialogInfo *property;
	zval *objvar;
	char _wxResource[] = "wxResource";
	
	char parse_parameters[] = "O";
	
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, parse_parameters, &objvar, php_wxAboutDialogInfo_entry) == FAILURE)
	{
		RETURN_NULL();
	}
	
	if(zend_hash_find(Z_OBJPROP_P(objvar), _wxResource, sizeof(_wxResource),  (void **)&tmp) == FAILURE) 
	{
		return;
	}
	
	id_to_find = Z_LVAL_PP(tmp);
	
	property = (wxAboutDialogInfo*) zend_list_find(id_to_find, &le_wxAboutDialogInfo);
	
	wxAboutBox(*property);
}

/**
 * Space reserved for autogenerated functions
 */
<?php print $functions ?>


static zend_function_entry php_wxWidgets_functions[] = {
	PHP_FALIAS(wxInitAllImageHandlers, php_wxInitAllImageHandlers, NULL)
	PHP_FALIAS(wxExecute, php_wxExecute, NULL)
	PHP_FALIAS(wxInitialize, php_wxInitialize, NULL)
	PHP_FALIAS(wxEntry, php_wxEntry, NULL)
	PHP_FALIAS(wxAboutBox, php_wxAboutBox, NULL)
	
	/**
	 * Space reserved for the addition to functions table of
	 * autogenerated functions
	 */
<?php print $functions_table ?>

	PHP_FE_END //Equivalent to { NULL, NULL, NULL, 0, 0 } at time of writing on PHP 5.4
};

PHP_RINIT_FUNCTION(php_wxWidgets)
{
	static int objects_intialized = 0;
	
	/**
	 * Space reserved for the initialization of global object 
	 * constants, since the php engine doesnt initializes the object
	 * store prior to calling extensions MINIT function.
	 * 
	 * Note:
	 * 
	 * Predefined fonts, pens brushes, colors and cursos are  initilized 
	 * by 'wxStockGDI::instance().Get*(item)' functions and it needs 
	 * wxInitilize call in order to work (learned this the hard way)
	 */
	 
	if(objects_intialized < 1)
	{
		wxInitialize();
	 
<?php print $object_constants ?>
	
		wxUninitialize(); //Maybe this shouldn't be called for references like wxNORMAL_FONT
		
		objects_intialized = 1;
	}
		
    return SUCCESS;
}

PHP_MINIT_FUNCTION(php_wxWidgets)
{
    zend_class_entry ce; /* Temporary variable used to initialize class entries */

	/**
	 * Predefined Initialization of wxApp class
	 */
	INIT_CLASS_ENTRY(ce, PHP_wxApp_NAME , php_wxApp_functions);
	php_wxApp_entry = zend_register_internal_class(&ce TSRMLS_CC);
	le_wxApp = zend_register_list_destructors_ex(NULL,NULL, le_wxApp_name ,module_number);	
	
	
	/**
	 * Space reserved for the initialization of autogenerated classes,
	 * class enumerations and global constants
	 */
	  
<?php print $classes ?>
	
    return SUCCESS;
}

/**
 * TODO: Automate the process of updating versions number
 * Show version information to phpinfo()
 */
PHP_MINFO_FUNCTION(php_wxWidgets)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "wxWidgets", "enabled");
	php_info_print_table_row(2, "Extension Version", PHP_WXWIDGETS_EXTVER);
	php_info_print_table_row(2, "wxWidgets Version", PHP_WXWIDGETS_VERSION);
	php_info_print_table_end();
}


/**
 * Declaration of wxWidgets module
 */
zend_module_entry wxWidgets_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
     STANDARD_MODULE_HEADER,
#endif
    PHP_WXWIDGETS_EXTNAME,
    php_wxWidgets_functions, 	/* Functions (module functions) */
    PHP_MINIT(php_wxWidgets), 	/* MINIT (module initialization function) */
    NULL, 						/* MSHUTDOWN (module shutdown function) */
    PHP_RINIT(php_wxWidgets),	/* RINIT (request initialization function) */
    NULL, 						/* RSHUTDOWN (request shutdown function) */
    NULL, 						/* MINFO (module information function) */
#if ZEND_MODULE_API_NO >= 20010901
    PHP_WXWIDGETS_EXTVER,
#endif
    STANDARD_MODULE_PROPERTIES
};

/**
 * Insertion of wxWidgets module to the PHP runtime
 */
#ifdef COMPILE_DL_WXWIDGETS
extern "C" {
ZEND_GET_MODULE(wxWidgets)
}
#endif
