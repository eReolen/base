<?php
namespace Bpi\Sdk;

/**
 * TODO please add a general description about the purpose of this class.
 */
class Authorization
{
    protected $agencyId;
    protected $publicKey;
    protected $secret;
    protected $token;

    /**
     *
     * @param string $agencyId
     * @param string $publicKey
     * @param string $secret
     */
    public function __construct($agencyId, $publicKey, $secret)
    {
        $this->agencyId = $agencyId;
        $this->publicKey = $publicKey;
        $this->secret = $secret;
        $this->generateToken();
    }

    /**
     * Generate authorization token
     */
    protected function generateToken()
    {
        $this->token = password_hash($this->agencyId . $this->publicKey . $this->secret, PASSWORD_BCRYPT);
    }

    /**
     * Represent as HTTP Authorization string.
     * Will return value part, e.g. Authorization: <value>
     *
     * @return string
     */
    public function toHTTPHeader()
    {
        return sprintf('BPI agency="%s", token="%s"', $this->agencyId, $this->token);
    }
}
