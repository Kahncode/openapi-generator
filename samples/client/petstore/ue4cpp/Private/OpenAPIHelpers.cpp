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
#include "OpenAPIHelpers.h"

#include "OpenAPIModule.h"

#include "Interfaces/IHttpRequest.h"
#include "PlatformHttp.h"
#include "Misc/FileHelper.h"

namespace OpenAPI 
{

HttpFileInput::HttpFileInput(const TCHAR* InFilePath)
{
	SetFilePath(InFilePath);
}

HttpFileInput::HttpFileInput(const FString& InFilePath)
{
	SetFilePath(InFilePath);
}

void HttpFileInput::SetFilePath(const TCHAR* InFilePath)
{
	FilePath = InFilePath;
	if(ContentType.IsEmpty())
	{
		ContentType = FPlatformHttp::GetMimeType(InFilePath);
	}
}

void HttpFileInput::SetFilePath(const FString& InFilePath)
{
	SetFilePath(*InFilePath);
}

void HttpFileInput::SetContentType(const TCHAR* InContentType)
{
	ContentType = InContentType;
}

FString HttpFileInput::GetFilename() const
{
	return FPaths::GetCleanFilename(FilePath);
}

//////////////////////////////////////////////////////////////////////////

const TCHAR* HttpMultipartFormData::Delimiter = TEXT("--");
const TCHAR* HttpMultipartFormData::Newline = TEXT("\r\n");

void HttpMultipartFormData::SetBoundary(const TCHAR* InBoundary)
{
	checkf(Boundary.IsEmpty(), TEXT("Boundary must be set before usage"));
	Boundary = InBoundary;
}

const FString& HttpMultipartFormData::GetBoundary() const
{
	if (Boundary.IsEmpty())
	{
		// Generate a random boundary with enough entropy, should avoid occurences of the boundary in the data.
		// Since the boundary is generated at every request, in case of failure, retries should succeed.
		Boundary = FGuid::NewGuid().ToString(EGuidFormats::Short);
	}

	return Boundary;
}

void HttpMultipartFormData::SetupHttpRequest(const TSharedRef<IHttpRequest>& HttpRequest)
{
	if(HttpRequest->GetVerb() != TEXT("POST"))
	{
		UE_LOG(LogOpenAPI, Error, TEXT("Expected POST verb when using multipart form data"));
	}

	// Append final boundary
	AppendString(Delimiter);
	AppendString(*GetBoundary());
	AppendString(Delimiter);

	HttpRequest->SetHeader("Content-Type", FString::Printf(TEXT("multipart/form-data; boundary=%s"), *GetBoundary()));
	HttpRequest->SetContent(FormData);
}

void HttpMultipartFormData::AddStringPart(const TCHAR* Name, const TCHAR* Data)
{
	// Add boundary
	AppendString(Delimiter);
	AppendString(*GetBoundary());
	AppendString(Newline);

	// Add header
	AppendString(*FString::Printf(TEXT("Content-Disposition: form-data; name = \"%s\""), Name));
	AppendString(Newline);
	AppendString(*FString::Printf(TEXT("Content-Type: text/plain; charset=utf-8")));
	AppendString(Newline);

	// Add header to body splitter
	AppendString(Newline);

	// Add Data
	AppendString(Data);
	AppendString(Newline);
}

void HttpMultipartFormData::AddJsonPart(const TCHAR* Name, const FString& JsonString)
{
	// Add boundary
	AppendString(Delimiter);
	AppendString(*GetBoundary());
	AppendString(Newline);

	// Add header
	AppendString(*FString::Printf(TEXT("Content-Disposition: form-data; name=\"%s\""), Name));
	AppendString(Newline);
	AppendString(*FString::Printf(TEXT("Content-Type: application/json; charset=utf-8")));
	AppendString(Newline);

	// Add header to body splitter
	AppendString(Newline);

	// Add Data
	AppendString(*JsonString);
	AppendString(Newline);
}

void HttpMultipartFormData::AddBinaryPart(const TCHAR* Name, const TArray<uint8>& ByteArray)
{
	// Add boundary
	AppendString(Delimiter);
	AppendString(*GetBoundary());
	AppendString(Newline);

	// Add header
	AppendString(*FString::Printf(TEXT("Content-Disposition: form-data; name=\"%s\""), Name));
	AppendString(Newline);
	AppendString(*FString::Printf(TEXT("Content-Type: application/octet-stream")));
	AppendString(Newline);

	// Add header to body splitter
	AppendString(Newline);

	// Add Data
	FormData.Append(ByteArray);
	AppendString(Newline);
}

void HttpMultipartFormData::AddFilePart(const TCHAR* Name, const HttpFileInput& File)
{
	TArray<uint8> FileContents;
	if (!FFileHelper::LoadFileToArray(FileContents, *File.GetFilePath()))
	{
		UE_LOG(LogOpenAPI, Error, TEXT("Failed to load file (%s)"), *File.GetFilePath());
		return;
	}

	// Add boundary
	AppendString(Delimiter);
	AppendString(*GetBoundary());
	AppendString(Newline);

	// Add header
	AppendString(*FString::Printf(TEXT("Content-Disposition: form-data; name=\"%s\"; filename=\"%s\""), Name, *File.GetFilename()));
	AppendString(Newline);
	AppendString(*FString::Printf(TEXT("Content-Type: %s"), *File.GetContentType()));
	AppendString(Newline);

	// Add header to body splitter
	AppendString(Newline);

	// Add Data
	FormData.Append(FileContents);
	AppendString(Newline);
}

void HttpMultipartFormData::AppendString(const TCHAR* Str)
{
	FTCHARToUTF8 utf8Str(Str);
	FormData.Append((uint8*)utf8Str.Get(), utf8Str.Length());
}

}
