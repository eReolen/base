<?php
namespace Bpi\Sdk;

class ResponseStatus
{
    protected $status;

    /**
     *
     * @param integer $status_code
     */
    public function __construct($status_code)
    {
        $this->status = (string) $status_code;

        if ($this->status <= 0)
            throw new \InvalidArgumentException('Incorrect HTTP status code [' . $status_code . ']');
    }

    public function __toString()
    {
        return (string) $this->status;
    }

    public function getCode()
    {
        return $this->status;
    }

    public function isSuccess()
    {
        return $this->status[0] == 2;
    }

    public function isClientError()
    {
        return $this->status[0] == 4;
    }

    public function isServerError()
    {
        return $this->status[0] == 5;
    }

    public function isError()
    {
        return $this->isClientError() || $this->isServerError();
    }
}
