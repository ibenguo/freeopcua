/// @author Alexander Rykovanov 2012
/// @email rykovanov.as@gmail.com
/// @brief Opc Ua Binary. Subscription services structs.
/// @license GNU LGPL
///
/// Distributed under the GNU LGPL License
/// (See accompanying file LICENSE or copy at
/// http://www.gnu.org/licenses/lgpl.html)
///

#include <opc/ua/protocol/binary/stream.h>
#include <opc/ua/protocol/subscriptions.h>

#include "binary_serialization.h"

namespace OpcUa
{
  ////////////////////////////////////////////////////////
  // SubscriptionParameters
  ////////////////////////////////////////////////////////

  SubscriptionParameters::SubscriptionParameters()
    : RequestedPublishingInterval(0)
    , RequestedLifetimeCount(1)
    , RequestedMaxKeepAliveCount(1)
    , MaxNotificationsPerPublish(1)
    , PublishingEnabled(true)
    , Priority(0)
  {
  }
  ////////////////////////////////////////////////////////
  // CreateSubscriptionRequest
  ////////////////////////////////////////////////////////

  CreateSubscriptionRequest::CreateSubscriptionRequest()
    : TypeID(CREATE_SUBSCRIPTION_REQUEST)
  {
  }

  ////////////////////////////////////////////////////////
  // SubscriptionData
  ////////////////////////////////////////////////////////

  SubscriptionData::SubscriptionData()
    : RevisedPublishingInterval(0)
    , RevisedLifetimeCount(1)
    , RevizedMaxKeepAliveCount(1)
  {
  }

  ////////////////////////////////////////////////////////
  // CreateSubscriptionResponse
  ////////////////////////////////////////////////////////

  CreateSubscriptionResponse::CreateSubscriptionResponse()
    : TypeID(CREATE_SUBSCRIPTION_RESPONSE)
  {
  }

  ////////////////////////////////////////////////////////
  // SubscriptionAcknowledgement
  ////////////////////////////////////////////////////////

  SubscriptionAcknowledgement::SubscriptionAcknowledgement()
    : SequenceNumber(0)
  {
  }

  ////////////////////////////////////////////////////////
  // PublishRequest
  ////////////////////////////////////////////////////////

  PublishRequest::PublishRequest()
    : TypeID(PUBLISH_REQUEST)
  {
  }

  ////////////////////////////////////////////////////////
  // PublishResult
  ////////////////////////////////////////////////////////

  PublishResult::PublishResult()
    : MoreNotifications(false)
  {
  }

  ////////////////////////////////////////////////////////
  // PublishResponse
  ////////////////////////////////////////////////////////

  PublishResponse::PublishResponse()
    : TypeID(PUBLISH_RESPONSE)
  {
  }

  ////////////////////////////////////////////////////////

  namespace Binary
  {
    ////////////////////////////////////////////////////////
    // SubscriptionParameters
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize<SubscriptionParameters>(const OpcUa::SubscriptionParameters& params)
    {
      return RawSize(params.RequestedPublishingInterval) +
          RawSize(params.RequestedLifetimeCount) +
          RawSize(params.RequestedMaxKeepAliveCount) +
          RawSize(params.MaxNotificationsPerPublish) +
          RawSize(params.PublishingEnabled) +
          RawSize(params.Priority);
    }

    template<>
    void IStream::Deserialize<SubscriptionParameters>(SubscriptionParameters& params)
    {
      *this >> params.RequestedPublishingInterval;
      *this >> params.RequestedLifetimeCount;
      *this >> params.RequestedMaxKeepAliveCount;
      *this >> params.MaxNotificationsPerPublish;
      *this >> params.PublishingEnabled;
      *this >> params.Priority;
    }

    template<>
    void OStream::Serialize<SubscriptionParameters>(const SubscriptionParameters& params)
    {
      *this << params.RequestedPublishingInterval;
      *this << params.RequestedLifetimeCount;
      *this << params.RequestedMaxKeepAliveCount;
      *this << params.MaxNotificationsPerPublish;
      *this << params.PublishingEnabled;
      *this << params.Priority;
    }

    ////////////////////////////////////////////////////////
    // CreateSubscriptionRequest
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const CreateSubscriptionRequest& request)
    {
      return RawSize(request.TypeID) +
        RawSize(request.Header) +
        RawSize(request.Parameters);
    }

    template<>
    void IStream::Deserialize<CreateSubscriptionRequest>(CreateSubscriptionRequest& request)
    {
      *this >> request.TypeID;
      *this >> request.Header;
      *this >> request.Parameters;
    }

    template<>
    void OStream::Serialize<CreateSubscriptionRequest>(const CreateSubscriptionRequest& request)
    {
      *this << request.TypeID;
      *this << request.Header;
      *this << request.Parameters;
    }

    ////////////////////////////////////////////////////////
    // SubscriptionData
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const SubscriptionData& data)
    {
      return RawSize(data.ID) +
        RawSize(data.RevisedPublishingInterval) +
        RawSize(data.RevisedLifetimeCount) +
        RawSize(data.RevizedMaxKeepAliveCount);
    }

    template<>
    void IStream::Deserialize<SubscriptionData>(SubscriptionData& data)
    {
      *this >> data.ID;
      *this >> data.RevisedPublishingInterval;
      *this >> data.RevisedLifetimeCount;
      *this >> data.RevizedMaxKeepAliveCount;
    }

    template<>
    void OStream::Serialize<SubscriptionData>(const SubscriptionData& data)
    {
      *this << data.ID;
      *this << data.RevisedPublishingInterval;
      *this << data.RevisedLifetimeCount;
      *this << data.RevizedMaxKeepAliveCount;
    }

    ////////////////////////////////////////////////////////
    // CreateSubscriptionResponse
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const CreateSubscriptionResponse& response)
    {
      return RawSize(response.TypeID) +
        RawSize(response.Header) +
        RawSize(response.Data);
    }

    template<>
    void IStream::Deserialize<CreateSubscriptionResponse>(CreateSubscriptionResponse& response)
    {
      *this >> response.TypeID;
      *this >> response.Header;
      *this >> response.Data;
    }

    template<>
    void OStream::Serialize<CreateSubscriptionResponse>(const CreateSubscriptionResponse& response)
    {
      *this << response.TypeID;
      *this << response.Header;
      *this << response.Data;
    }

    ////////////////////////////////////////////////////////
    // SubscriptionAcknowledgement
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const SubscriptionAcknowledgement& ack)
    {
      return RawSize(ack.SubscriptionID) + RawSize(ack.SequenceNumber);
    }

    template<>
    void IStream::Deserialize<SubscriptionAcknowledgement>(SubscriptionAcknowledgement& ack)
    {
      *this >> ack.SubscriptionID;
      *this >> ack.SequenceNumber;
    }

    template<>
    void OStream::Serialize<SubscriptionAcknowledgement>(const SubscriptionAcknowledgement& ack)
    {
      *this << ack.SubscriptionID;
      *this << ack.SequenceNumber;
    }

    template<>
    std::size_t RawSize(const std::vector<SubscriptionAcknowledgement>& ack)
    {
      return RawSizeContainer(ack);
    }

    template<>
    void IStream::Deserialize<std::vector<SubscriptionAcknowledgement>>(std::vector<SubscriptionAcknowledgement>& ack)
    {
      DeserializeContainer(*this, ack);
    }

    template<>
    void OStream::Serialize<std::vector<SubscriptionAcknowledgement>>(const std::vector<SubscriptionAcknowledgement>& ack)
    {
      SerializeContainer(*this, ack);
    }


    ////////////////////////////////////////////////////////
    // PublishParameters
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const PublishParameters& params)
    {
      return RawSize(params.Acknowledgements);
    }

    template<>
    void IStream::Deserialize<PublishParameters>(PublishParameters& params)
    {
      *this >> params.Acknowledgements;
    }

    template<>
    void OStream::Serialize<PublishParameters>(const PublishParameters& params)
    {
      *this << params.Acknowledgements;
    }

    ////////////////////////////////////////////////////////
    // PublishRequest
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const PublishRequest& request)
    {
      return RawSize(request.TypeID) + RawSize(request.Header) + RawSize(request.Parameters);
    }

    template<>
    void IStream::Deserialize<PublishRequest>(PublishRequest& request)
    {
      *this >> request.TypeID;
      *this >> request.Header;
      *this >> request.Parameters;
    }

    template<>
    void OStream::Serialize<PublishRequest>(const PublishRequest& request)
    {
      *this << request.TypeID;
      *this << request.Header;
      *this << request.Parameters;
    }

    ////////////////////////////////////////////////////////
    // PublishResult
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const PublishResult& result)
    {
      return RawSize(result.SubscriptionID) +
        RawSizeContainer(result.AvailableSequenceNumber) +
        RawSize(result.MoreNotifications) +
        RawSize(result.Message.Header) +
        RawSizeContainer(result.Statuses) +
        RawSizeContainer(result.Diagnostics);
    }

    template<>
    void IStream::Deserialize<PublishResult>(PublishResult& result)
    {
      *this >> result.SubscriptionID;
      DeserializeContainer(*this, result.AvailableSequenceNumber);
      *this >> result.MoreNotifications;
      *this >> result.Message.Header;// TODO Add serialization of Notofication message
      DeserializeContainer(*this, result.Statuses);
      DeserializeContainer(*this, result.Diagnostics);
    }

    template<>
    void OStream::Serialize<PublishResult>(const PublishResult& result)
    {
      *this << result.SubscriptionID;
      SerializeContainer(*this, result.AvailableSequenceNumber);
      *this << result.MoreNotifications;
      *this << result.Message.Header;// TODO Add serialization of Notofication message
      SerializeContainer(*this, result.Statuses);
      SerializeContainer(*this, result.Diagnostics);
    }

    ////////////////////////////////////////////////////////
    // PublishResponse
    ////////////////////////////////////////////////////////

    template<>
    std::size_t RawSize(const PublishResponse& response)
    {
      return RawSize(response.TypeID) + RawSize(response.Header) + RawSize(response.Result);
    }

    template<>
    void IStream::Deserialize<PublishResponse>(PublishResponse& response)
    {
      *this >> response.TypeID;
      *this >> response.Header;
      *this >> response.Result;
    }

    template<>
    void OStream::Serialize<PublishResponse>(const PublishResponse& response)
    {
      *this << response.TypeID;
      *this << response.Header;
      *this << response.Result;
    }

  } // namespace Binary
} // namespace OpcUa
