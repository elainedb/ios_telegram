#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MTSignal;

@interface TONError : NSObject

@property (nonatomic, strong, readonly) NSString *text;

@end

@interface TONKey : NSObject

@property (nonatomic, strong, readonly) NSString *publicKey;
@property (nonatomic, strong, readonly) NSData *secret;

- (instancetype)initWithPublicKey:(NSString *)publicKey secret:(NSData *)secret;

@end

@interface TONTransactionId : NSObject

@property (nonatomic, readonly) int64_t lt;
@property (nonatomic, strong, readonly) NSData * _Nonnull transactionHash;

- (instancetype)initWithLt:(int64_t)lt transactionHash:(NSData * _Nonnull)transactionHash;

@end

@interface TONAccountState : NSObject

@property (nonatomic, readonly) bool isInitialized;
@property (nonatomic, readonly) int64_t balance;
@property (nonatomic, readonly) int32_t seqno;
@property (nonatomic, strong, readonly) TONTransactionId * _Nullable lastTransactionId;
@property (nonatomic, readonly) int64_t syncUtime;

- (instancetype)initWithIsInitialized:(bool)isInitialized balance:(int64_t)balance seqno:(int32_t)seqno lastTransactionId:(TONTransactionId * _Nullable)lastTransactionId syncUtime:(int64_t)syncUtime;

@end

@interface TONTransactionMessage : NSObject

@property (nonatomic, readonly) int64_t value;
@property (nonatomic, strong, readonly) NSString * _Nonnull source;
@property (nonatomic, strong, readonly) NSString * _Nonnull destination;
@property (nonatomic, strong, readonly) NSString * _Nonnull textMessage;

- (instancetype)initWithValue:(int64_t)value source:(NSString * _Nonnull)source destination:(NSString * _Nonnull)destination textMessage:(NSString * _Nonnull)textMessage;

@end

@interface TONTransaction : NSObject

@property (nonatomic, strong, readonly) NSData * _Nonnull data;
@property (nonatomic, strong, readonly) TONTransactionId * _Nonnull transactionId;
@property (nonatomic, readonly) int64_t timestamp;
@property (nonatomic, readonly) int64_t fee;
@property (nonatomic, strong, readonly) TONTransactionMessage * _Nullable inMessage;
@property (nonatomic, strong, readonly) NSArray<TONTransactionMessage *> * _Nonnull outMessages;

- (instancetype)initWithData:(NSData * _Nonnull)data transactionId:(TONTransactionId * _Nonnull)transactionId timestamp:(int64_t)timestamp fee:(int64_t)fee inMessage:(TONTransactionMessage * _Nullable)inMessage outMessages:(NSArray<TONTransactionMessage *> * _Nonnull)outMessages;

@end

@interface TONExternalRequest : NSObject

@property (nonatomic, strong, readonly) NSData * _Nonnull data;
@property (nonatomic, copy, readonly) void (^onResult)(NSData * _Nullable, NSString * _Nullable);

- (instancetype)initWithData:(NSData * _Nonnull)data onResult:(void (^)(NSData * _Nullable, NSString * _Nullable))onResult;

@end

@interface TON : NSObject

- (instancetype)initWithKeystoreDirectory:(NSString *)keystoreDirectory config:(NSString *)config performExternalRequest:(void (^)(TONExternalRequest * _Nonnull))performExternalRequest;

- (MTSignal *)createKeyWithLocalPassword:(NSData *)localPassword mnemonicPassword:(NSData *)mnemonicPassword;
- (MTSignal *)getTestWalletAccountAddressWithPublicKey:(NSString *)publicKey;
- (MTSignal *)getTestGiverAccountState;
- (MTSignal *)getTestGiverAddress;
- (MTSignal *)testGiverSendGramsWithAccountState:(TONAccountState *)accountState accountAddress:(NSString *)accountAddress amount:(int64_t)amount;
- (MTSignal *)getAccountStateWithAddress:(NSString *)accountAddress;
- (MTSignal *)sendGramsFromKey:(TONKey *)key localPassword:(NSData *)localPassword fromAddress:(NSString *)fromAddress toAddress:(NSString *)address amount:(int64_t)amount textMessage:(NSString *)textMessage;
- (MTSignal *)exportKey:(TONKey *)key localPassword:(NSData *)localPassword;
- (MTSignal *)importKeyWithLocalPassword:(NSData *)localPassword mnemonicPassword:(NSData *)mnemonicPassword wordList:(NSArray<NSString *> *)wordList;
- (MTSignal *)deleteKeyWithPublicKey:(NSString *)publicKey;
- (MTSignal *)makeWalletInitialized:(TONKey *)key localPassword:(NSData *)localPassword;
- (MTSignal *)getTransactionListWithAddress:(NSString * _Nonnull)address lt:(int64_t)lt hash:(NSData * _Nonnull)hash;

@end

NS_ASSUME_NONNULL_END
