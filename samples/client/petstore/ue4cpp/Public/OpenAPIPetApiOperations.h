/**
 * OpenAPI Petstore
 * This is a sample server Petstore server. For this sample, you can use the api key `special-key` to test the authorization filters.
 *
 * OpenAPI spec version: 1.0.0
 * 
 *
 * NOTE: This class is auto generated by the swagger code generator program.
 * https://github.com/swagger-api/swagger-codegen.git
 * Do not edit the class manually.
 */
#pragma once

#include "OpenAPIBaseModel.h"
#include "OpenAPIPetApi.h"

#include "OpenAPIHelpers.h"
#include "OpenAPIApiResponse.h"
#include "OpenAPIPet.h"

namespace OpenAPI 
{

/* Add a new pet to the store

*/
class OPENAPI_API OpenAPIPetApi::AddPetRequest : public Request
{
public:
    virtual ~AddPetRequest() {}
	void SetupHttpRequest(const TSharedRef<IHttpRequest>& HttpRequest) const final;
	FString ComputePath() const final;
    
	/* Pet object that needs to be added to the store */
	std::shared_ptr<OpenAPIOpenAPIPet> Body;
};

class OPENAPI_API OpenAPIPetApi::AddPetResponse : public Response
{
public:
    virtual ~AddPetResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonObject) final;
    
    
};

/* Deletes a pet

*/
class OPENAPI_API OpenAPIPetApi::DeletePetRequest : public Request
{
public:
    virtual ~DeletePetRequest() {}
	void SetupHttpRequest(const TSharedRef<IHttpRequest>& HttpRequest) const final;
	FString ComputePath() const final;
    
	/* Pet id to delete */
	int64 PetId = 0;
	TOptional<FString> ApiKey;
};

class OPENAPI_API OpenAPIPetApi::DeletePetResponse : public Response
{
public:
    virtual ~DeletePetResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonObject) final;
    
    
};

/* Finds Pets by status
 *
 * Multiple status values can be provided with comma separated strings
*/
class OPENAPI_API OpenAPIPetApi::FindPetsByStatusRequest : public Request
{
public:
    virtual ~FindPetsByStatusRequest() {}
	void SetupHttpRequest(const TSharedRef<IHttpRequest>& HttpRequest) const final;
	FString ComputePath() const final;
    
	enum class StatusEnum
	{
		Available,
		Pending,
		Sold,
  	};
	/* Status values that need to be considered for filter */
	TArray<std::shared_ptr<StatusEnum>> Status;
};

class OPENAPI_API OpenAPIPetApi::FindPetsByStatusResponse : public Response
{
public:
    virtual ~FindPetsByStatusResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonObject) final;
    
    TArray<std::shared_ptr<OpenAPIOpenAPIPet>> Content;
};

/* Finds Pets by tags
 *
 * Multiple tags can be provided with comma separated strings. Use tag1, tag2, tag3 for testing.
*/
class OPENAPI_API OpenAPIPetApi::FindPetsByTagsRequest : public Request
{
public:
    virtual ~FindPetsByTagsRequest() {}
	void SetupHttpRequest(const TSharedRef<IHttpRequest>& HttpRequest) const final;
	FString ComputePath() const final;
    
	/* Tags to filter by */
	TArray<std::shared_ptr<FString>> Tags;
};

class OPENAPI_API OpenAPIPetApi::FindPetsByTagsResponse : public Response
{
public:
    virtual ~FindPetsByTagsResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonObject) final;
    
    TArray<std::shared_ptr<OpenAPIOpenAPIPet>> Content;
};

/* Find pet by ID
 *
 * Returns a single pet
*/
class OPENAPI_API OpenAPIPetApi::GetPetByIdRequest : public Request
{
public:
    virtual ~GetPetByIdRequest() {}
	void SetupHttpRequest(const TSharedRef<IHttpRequest>& HttpRequest) const final;
	FString ComputePath() const final;
    
	/* ID of pet to return */
	int64 PetId = 0;
};

class OPENAPI_API OpenAPIPetApi::GetPetByIdResponse : public Response
{
public:
    virtual ~GetPetByIdResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonObject) final;
    
    OpenAPIPet Content;
};

/* Update an existing pet

*/
class OPENAPI_API OpenAPIPetApi::UpdatePetRequest : public Request
{
public:
    virtual ~UpdatePetRequest() {}
	void SetupHttpRequest(const TSharedRef<IHttpRequest>& HttpRequest) const final;
	FString ComputePath() const final;
    
	/* Pet object that needs to be added to the store */
	std::shared_ptr<OpenAPIOpenAPIPet> Body;
};

class OPENAPI_API OpenAPIPetApi::UpdatePetResponse : public Response
{
public:
    virtual ~UpdatePetResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonObject) final;
    
    
};

/* Updates a pet in the store with form data

*/
class OPENAPI_API OpenAPIPetApi::UpdatePetWithFormRequest : public Request
{
public:
    virtual ~UpdatePetWithFormRequest() {}
	void SetupHttpRequest(const TSharedRef<IHttpRequest>& HttpRequest) const final;
	FString ComputePath() const final;
    
	/* ID of pet that needs to be updated */
	int64 PetId = 0;
	/* Updated name of the pet */
	TOptional<FString> Name;
	/* Updated status of the pet */
	TOptional<FString> Status;
};

class OPENAPI_API OpenAPIPetApi::UpdatePetWithFormResponse : public Response
{
public:
    virtual ~UpdatePetWithFormResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonObject) final;
    
    
};

/* uploads an image

*/
class OPENAPI_API OpenAPIPetApi::UploadFileRequest : public Request
{
public:
    virtual ~UploadFileRequest() {}
	void SetupHttpRequest(const TSharedRef<IHttpRequest>& HttpRequest) const final;
	FString ComputePath() const final;
    
	/* ID of pet to update */
	int64 PetId = 0;
	/* Additional data to pass to server */
	TOptional<FString> AdditionalMetadata;
	/* file to upload */
	TOptional<HttpFileInput> File;
};

class OPENAPI_API OpenAPIPetApi::UploadFileResponse : public Response
{
public:
    virtual ~UploadFileResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonObject) final;
    
    OpenAPIApiResponse Content;
};

}
